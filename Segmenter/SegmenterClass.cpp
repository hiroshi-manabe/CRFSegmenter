#include "SegmenterClass.h"

#include "../HighOrderCRF/AggregatedFeatureTemplateGenerator.h"
#include "../HighOrderCRF/HighOrderCRFProcessor.h"
#include "../HighOrderCRF/ObservationSequence.h"
#include "../HighOrderCRF/UnconditionalFeatureTemplateGenerator.h"
#include "../optionparser/optionparser.h"
#include "../task/task_queue.hpp"
#include "CharacterFeatureGenerator.h"
#include "CharacterTypeFeatureGenerator.h"
#include "CharWithSpace.h"
#include "CharWithSpaceFeatureGenerator.h"
#include "CharWithSpaceTypeFeatureGenerator.h"
#include "DictionaryFeatureGenerator.h"
#include "SegmenterOptions.h"
#include "UnicodeCharacter.h"

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Segmenter {

using HighOrderCRF::AggregatedFeatureTemplateGenerator;
using HighOrderCRF::FeatureTemplateGenerator;
using HighOrderCRF::HighOrderCRFProcessor;
using HighOrderCRF::ObservationSequence;
using HighOrderCRF::UnconditionalFeatureTemplateGenerator;

using std::endl;
using std::cin;
using std::cout;
using std::cerr;
using std::future;
using std::getline;
using std::ifstream;
using std::make_shared;
using std::ofstream;
using std::queue;
using std::shared_ptr;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::unordered_set;
using std::vector;

vector<string> splitString(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

static vector<string> splitStringByTabs(const string &s) {
    return splitString(s, '\t');
}

shared_ptr<ObservationSequence<CharWithSpace>> convertLineToObservationSequence(const string &line, bool hasValidLabels, const SegmenterOptions &flags) {
    const char *buf = line.c_str();
    size_t len = line.size();
    bool prevIsSpace = true;
    bool prevIsOrigSpace = false;
    auto observationList = make_shared<vector<CharWithSpace>>();
    auto labelList = make_shared<vector<string>>();

    size_t pos = 0;
    bool isAfterSlash = false;
    auto possibleLabelSetList = make_shared<vector<unordered_set<string>>>(observationList->size());
    string prevCharType;

    while (pos < len) {
        size_t charCount = 0;
        auto uchar = UnicodeCharacter::fromString(buf + pos, len, &charCount);
        pos += charCount;
        bool isNBSP = uchar.getCodePoint() == 0xa0;
        bool isSpace = uchar.getCodePoint() == 0x20 || (!flags.asciiSpaceOnly && (uchar.getCodePoint() == 0x3000 || isNBSP));

        if (flags.isTraining && ((flags.containsSpaces && isNBSP) || (!flags.containsSpaces && isSpace))) {
            prevIsSpace = true;
            continue;
        }
        else if (isSpace) {
            prevIsOrigSpace = true;
            continue;
        }
        else {
            if (observationList->empty()) {
                prevIsOrigSpace = true;
            }
            observationList->push_back(CharWithSpace(uchar, prevIsOrigSpace));
            string charType = uchar.getCharacterType();

            labelList->push_back((prevIsSpace || prevIsOrigSpace) ? "1" : "0");
            unordered_set<string> possibleLabelSet;

            bool cutFlag = false;
            bool noCutFlag = false;

            if (prevIsOrigSpace || (flags.ignoreLatin && prevCharType == "LATIN" && charType == "LATIN" && prevIsSpace)) {
                cutFlag = true;
            }
            else if ((flags.concatenateOnly || (flags.ignoreLatin && prevCharType == "LATIN" && charType == "LATIN")) && !prevIsSpace) {
                noCutFlag = true;
            }

            if (cutFlag) {
                possibleLabelSet = decltype(possibleLabelSet){ "1" };
            }
            else if (noCutFlag) {
                possibleLabelSet = decltype(possibleLabelSet){ "0" };
            }
            else {
                possibleLabelSet = decltype(possibleLabelSet){ "0", "1" };
            }

            possibleLabelSetList->push_back(move(possibleLabelSet));
            prevIsSpace = false;
            prevIsOrigSpace = false;
            prevCharType = move(charType);
        }
    }
    return make_shared<ObservationSequence<CharWithSpace>>(observationList, labelList, possibleLabelSetList, hasValidLabels);
}

vector<shared_ptr<ObservationSequence<CharWithSpace>>> readData(const string &fileName, bool hasValidLabels, const SegmenterOptions &flags) {
    ifstream ifs(fileName);
    if (!ifs.is_open()) {
        cerr << "Cannot read from file: " << fileName << endl;
        exit(1);
    }
    vector<shared_ptr<ObservationSequence<CharWithSpace>>> observationSequenceList;
    string line;
    while (getline(ifs, line)) {
        auto seq = convertLineToObservationSequence(line, hasValidLabels, flags);
        if (seq->empty()) {
            continue;
        }
        observationSequenceList.push_back(seq);
    }
    ifs.close();
    return observationSequenceList;
}

enum optionIndex { UNKNOWN, HELP, TRAIN, SEGMENT, CONTAINS_SPACES, CONCATENATE_ONLY, CALC_LIKELIHOOD, ASCII_SPACE_ONLY, PRESERVE_SPACES, IGNORE_LATIN, TEST, MODEL, DICT, THREADS, CHAR_N, CHAR_W, CHAR_L, TYPE_N, TYPE_W, TYPE_L, WORD_L, REGTYPE, COEFF, EPSILON, MAXITER };
vector<string> optionsToSave { "CONTAINS_SPACES", "CONCATENATE_ONLY", "ASCII_SPACE_ONLY", "CHAR_N", "CHAR_W", "CHAR_L", "TYPE_N", "TYPE_W", "TYPE_L", "WORD_L" };

struct Arg : public option::Arg
{
    static option::ArgStatus Required(const option::Option& option, bool msg)
    {
        if (option.arg != 0) {
            return option::ARG_OK;
        }
        return option::ARG_ILLEGAL;
    }
};

const option::Descriptor usage[] =
{
    { UNKNOWN, "UNKNOWN", 0, "", "", Arg::None, "USAGE:  [options]\n\n"
    "Options:" },
    { HELP, "HELP", 0, "h", "help", Arg::None, "  -h, --help  \tPrints usage and exit." },
    { MODEL, "MODEL", 0, "", "model", Arg::Required, "  --model  <file>\tDesignates the model file to be saved/loaded." },
    { DICT, "DICT", 0, "", "dict", Arg::Required, "  --dict  <file>\tDesignates the dictionary file to be loaded." },
    { CHAR_N, "CHAR_N", 0, "", "charn", Arg::Required, "  --charn  <number>\tN-gram length of characters. Defaults to 3." },
    { CHAR_W, "CHAR_W", 0, "", "charw", Arg::Required, "  --charw  <number>\tWindow width for characters. Defaults to 3." },
    { CHAR_L, "CHAR_L", 0, "", "charl", Arg::Required, "  --charl  <number>\tMaximum label length of characters. Defaults to 4." },
    { TYPE_N, "TYPE_N", 0, "", "typen", Arg::Required, "  --typen  <number>\tN-gram length of character types. Defaults to 3." },
    { TYPE_W, "TYPE_W", 0, "", "typew", Arg::Required, "  --typew  <number>\tWindow width for character types. Defaults to 3." },
    { TYPE_L, "TYPE_L", 0, "", "typel", Arg::Required, "  --typel  <number>\tMaximum label length of character types. Defaults to 1." },
    { WORD_L, "WORD_L", 0, "", "wordl", Arg::Required, "  --wordl  <number>\tMaximum label length of dictionary words. Defaults to 5." },
    { SEGMENT, "SEGMENT", 0, "", "segment", Arg::None, "  --segment  \tSegments text read from the standard input and writes the result to the standard output. This option can be omitted." },
    { CONTAINS_SPACES, "CONTAINS_SPACES", 0, "", "contains-spaces", Arg::None, "  --contains-spaces  \tIndicates that the original text contains spaces (e.g. Korean). In this case, spaces in the original text should be represented by U+0020 and additional spaces should be represented by U+00A0." },
    { CONCATENATE_ONLY, "CONCATENATE_ONLY", 0, "", "concatenate-only", Arg::None, "  --concatenate-only  \tDoes not segment and only concatenates words." },
    { CALC_LIKELIHOOD, "CALC_LIKELIHOOD", 0, "", "calc-likelihood", Arg::None, "  --calc-likelihood  \tCalculates the likelihoods of cutting at each position." },
    { ASCII_SPACE_ONLY, "ASCII_SPACE_ONLY", 0, "", "ascii-space-only", Arg::None, "  --ascii-space-only  \tUses only ascii spaces for segmentation." },
    { IGNORE_LATIN, "IGNORE_LATIN", 0, "", "ignore-latin", Arg::None, "  --ignore-latin  \tPrevents the segmenter from cutting between latin characters. Ignored when training or testing." },
    { TEST, "TEST", 0, "", "test", Arg::Required, "  --test  <file>\tTests the model with the given file." },
    { TRAIN, "TRAIN", 0, "", "train", Arg::Required, "  --train  <file>\tTrains the model on the given file." },
    { REGTYPE, "REGTYPE", 0, "", "regtype", Arg::Required, "  --regtype  <type>\tDesignates the regularization type (\"L1\" / \"L2\") for optimization." },
    { COEFF, "COEFF", 0, "", "coeff", Arg::Required, "  --coeff  <number>\tSets the regularization coefficient." },
    { EPSILON, "EPSILON", 0, "", "epsilon", Arg::Required, "  --epsilon  <number>\tSets the epsilon for convergence." },
    { MAXITER, "MAXITER", 0, "", "maxiter", Arg::Required, "  --maxiter  <number>\tSets the maximum iteration count." },
    { THREADS, "THREADS", 0, "", "threads", Arg::Required, "  --threads  <number>\tDesignates the number of threads to run concurrently." },
    { UNKNOWN, "UNKNOWN", 0, "", "", Arg::None, "Examples:\n"
    "  Segmenter --train train.txt --model model.dat\n"
    "  Segmenter --test test.txt --model model.dat\n"
    "  Segmenter --segment < input_file > output_file"
    },
    { 0, 0, 0, 0, 0, 0 }
};

bool fileExists(const string &filename) {
    ifstream infile(filename.c_str());
    return infile.good();
}

void readOptions(const string &filename, const vector<string> &optionsToSave, unordered_map<string, string> *optionMap) {
    ifstream ifs(filename.c_str());
    if (!ifs.is_open()) {
        cerr << "Cannot read from file: " << filename << endl;
        exit(1);
    }
    string line;
    while (getline(ifs, line)) {
        vector<string> elems = splitStringByTabs(line);
        if (elems.size() != 2) {
            cerr << "Corrupt file: " << filename << endl;
            exit(1);
        }
        (*optionMap)[elems[0]] = elems[1];
    }
}

void writeOptions(const string &filename, const vector<string> &optionsToSave, const unordered_map<string, string> &optionMap) {
    ofstream ofs(filename.c_str());
    if (!ofs.is_open()) {
        cerr << "Cannot write to file: " << filename << endl;
        exit(1);
    }
    for (const auto &entry : optionMap) {
        bool flag = false;
        for (const auto &elem : optionsToSave) {
            if (elem == entry.first) {
                flag = true;
            }
        }
        if (flag) {
            ofs << entry.first << "\t" << entry.second << endl;
        }
    }
}

int mainProc(int argc, char **argv) {
    Segmenter::SegmenterOptions op = { 3, 3, 4, 3, 3, 1, 5, 1 };

    argv += (argc > 0);
    argc -= (argc > 0);

    option::Stats stats(usage, argc, argv);
    vector<option::Option> options(stats.options_max);
    vector<option::Option> buffer(stats.buffer_max);
    option::Parser parse(usage, argc, argv, options.data(), buffer.data());

    if (parse.error()) {
        return 1;
    }

    unordered_map<string, string> optionMap;
    for (auto &option : options) {
        if (option.count() > 0) {
            optionMap[option.desc->name] = (option.arg ? option.arg : "");
        }
    }

    string modelFilename;
    if (optionMap.find("MODEL") != optionMap.end()) {
        modelFilename = optionMap["MODEL"];
        string optionFilename = modelFilename + ".options";
        if (optionMap.find("TRAIN") == optionMap.end() && fileExists(optionFilename)) {
            readOptions(optionFilename, optionsToSave, &optionMap);
        }
    }
    else {
        option::printUsage(cerr, usage);
        return 0;
    }

    if (optionMap.find("HELP") != optionMap.end()) {
        option::printUsage(cout, usage);
        return 0;
    }

    string dictFilename;
    if (optionMap.find("DICT") != optionMap.end()) {
        dictFilename = optionMap["DICT"];
        op.dictionaryFilename = dictFilename;
    }

    op.numThreads = 1;
    if (optionMap.find("THREADS") != optionMap.end()) {
        int num = atoi(optionMap["THREADS"].c_str());
        if (num < 1) {
            cerr << "Illegal number of threads" << endl;
            exit(1);
        }
        op.numThreads = num;
    }

    if (optionMap.find("CHAR_N") != optionMap.end()) {
        op.charMaxNgram = atoi(optionMap["CHAR_N"].c_str());
    }
    if (optionMap.find("CHAR_W") != optionMap.end()) {
        op.charMaxWindow = atoi(optionMap["CHAR_W"].c_str());
    }
    if (optionMap.find("CHAR_L") != optionMap.end()) {
        op.charMaxLabelLength = atoi(optionMap["CHAR_L"].c_str());
    }
    if (optionMap.find("TYPE_N") != optionMap.end()) {
        op.charMaxNgram = atoi(optionMap["TYPE_N"].c_str());
    }
    if (optionMap.find("TYPE_W") != optionMap.end()) {
        op.charMaxWindow = atoi(optionMap["TYPE_W"].c_str());
    }
    if (optionMap.find("TYPE_L") != optionMap.end()) {
        op.charMaxLabelLength = atoi(optionMap["TYPE_L"].c_str());
    }
    op.asciiSpaceOnly = optionMap.find("ASCII_SPACE_ONLY") != optionMap.end() ? true : false;
    op.containsSpaces = optionMap.find("CONTAINS_SPACES") != optionMap.end() ? true : false;
    op.isTraining = false;
        
    if (optionMap.find("TRAIN") != optionMap.end()) {
        op.isTraining = true;
        string trainingFilename = optionMap["TRAIN"];

        if (optionMap.find("COEFF") != optionMap.end()) {
            op.coeff = atof(optionMap["COEFF"].c_str());
        }
        if (optionMap.find("EPSILON") != optionMap.end()) {
            op.epsilon = atof(optionMap["EPSILON"].c_str());
        }
        if (optionMap.find("MAXITER") != optionMap.end()) {
            op.epsilon = atoi(optionMap["MAXITER"].c_str());
        }
        if (optionMap.find("REGTYPE") != optionMap.end()) {
            op.regType = optionMap["REGTYPE"];
        }

        Segmenter::SegmenterClass s(op);
        s.train(trainingFilename, modelFilename);
        string optionFilename = modelFilename + ".options";
        writeOptions(optionFilename, optionsToSave, optionMap);
        
        return 0;
    }

    if (optionMap.find("TEST") != optionMap.end()) {
        string testFilename = optionMap["TEST"];
        Segmenter::SegmenterClass s(op);
        s.readModel(modelFilename);
        s.test(testFilename);
        return 0;
    }

    // --segment or --calc-likelihood
    op.concatenateOnly = optionMap.find("CONCATENATE_ONLY") != optionMap.end() ? true : false;
    op.ignoreLatin = optionMap.find("IGNORE_LATIN") != optionMap.end() ? true : false;

    Segmenter::SegmenterClass s(op);
    s.readModel(modelFilename);
    
    string line;
    hwm::task_queue tq(op.numThreads);
    queue<future<string>> futureQueue;
    
    while (getline(cin, line)) {
        future<string> f = optionMap.find("CALC_LIKELIHOOD") != optionMap.end() ? tq.enqueue(&Segmenter::SegmenterClass::calcLabelLikelihoods, s, line) :
            tq.enqueue(&Segmenter::SegmenterClass::segment, s, line);
        futureQueue.push(move(f));
        if (op.numThreads == 1) {
            futureQueue.front().wait();
        }
        while (!futureQueue.empty() && futureQueue.front().wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            cout << futureQueue.front().get() << endl;
            futureQueue.pop();
        }
    }
    while (!futureQueue.empty()) {
        futureQueue.front().wait();
        cout << futureQueue.front().get() << endl;
        futureQueue.pop();
    }

    return 0;
}

SegmenterClass::SegmenterClass(const SegmenterOptions &options) {
    this->options = options;
    auto gen = make_shared<AggregatedFeatureTemplateGenerator<CharWithSpace>>();
    gen->addFeatureTemplateGenerator(make_shared<UnconditionalFeatureTemplateGenerator<CharWithSpace>>(1));
    gen->addFeatureTemplateGenerator(make_shared<CharacterFeatureGenerator>(options.charMaxNgram,
                                                                            options.charMaxWindow,
                                                                            options.charMaxLabelLength));
    gen->addFeatureTemplateGenerator(make_shared<CharacterTypeFeatureGenerator>(options.charTypeMaxNgram,
                                                                                options.charTypeMaxWindow,
                                                                                options.charTypeMaxLabelLength));
    if (options.containsSpaces) {
    gen->addFeatureTemplateGenerator(make_shared<CharWithSpaceFeatureGenerator>(options.charMaxNgram,
                                                                                options.charMaxWindow,
                                                                                options.charMaxLabelLength));
    gen->addFeatureTemplateGenerator(make_shared<CharWithSpaceTypeFeatureGenerator>(options.charTypeMaxNgram,
                                                                                    options.charTypeMaxWindow,
                                                                                    options.charTypeMaxLabelLength));
    }
    if (!options.dictionaryFilename.empty()) {
        gen->addFeatureTemplateGenerator(make_shared<DictionaryFeatureGenerator>(options.dictionaryFilename, options.wordMaxLabelLength));
    }
    featureGenerator = gen;
};

void SegmenterClass::train(const string &trainingFilename,
                           const string &modelFilename) {

    auto observationSequenceList = readData(trainingFilename, true, options);
    CRFProcessor = make_shared<HighOrderCRFProcessor<CharWithSpace>>();
    unordered_set<string> labelSet;
    labelSet.insert("0");
    labelSet.insert("1");
    bool isL1 = false;
    if (!options.regType.empty() && options.regType != "L1" && options.regType != "L2") {
        cerr << "Unsupported regularization type: " << options.regType;
    }
    isL1 = (options.regType == "L1");
    CRFProcessor->train(observationSequenceList, *featureGenerator, labelSet, options.numThreads, options.maxIter, isL1, options.coeff, options.epsilon);
    CRFProcessor->writeModel(modelFilename);
}

string SegmenterClass::segment(const string &line) const {
    if (line.empty()) {
        return "";
    }
    auto observationSequence = convertLineToObservationSequence(line, false, options);
    if (observationSequence->empty()) {
        return "";
    }
    auto spaceList = CRFProcessor->tag(*observationSequence, *featureGenerator);
    auto unicodeList = observationSequence->getObservationList();
    string ret;
    for (size_t i = 0; i < unicodeList->size(); ++i) {
        if (i > 0 && (*spaceList)[i] == "1") {
            ret += " ";
        }
        ret += (*unicodeList)[i].getUnicodeCharacter().toString();
    }
    return ret;
}

string SegmenterClass::calcLabelLikelihoods(const string &line) {
    if (line.empty()) {
        return "";
    }
    auto observationSequence = convertLineToObservationSequence(line, false, options);
    if (observationSequence->empty()) {
        return "";
    }
    auto unicodeList = observationSequence->getObservationList();
    auto likelihoods = CRFProcessor->calcLabelLikelihoods(*observationSequence, *featureGenerator);
    stringstream ss;
    for (size_t i = 0; i < unicodeList->size(); ++i) {
        const auto &labelMap = likelihoods[i];
        ss << (*unicodeList)[i].toString();
        for (const auto &entry : labelMap) {
            ss << "\t" << entry.first << ":" << entry.second;
        }
        ss << endl;
    }
    return ss.str();
}

void SegmenterClass::test(const string &testFilename) {
    auto observationSequenceList = readData(testFilename, true, options);
    vector<shared_ptr<vector<string>>> labelListList;
    for (auto &observationSequence : observationSequenceList) {
        labelListList.push_back(observationSequence->getLabelList());
    }
    CRFProcessor->test(observationSequenceList, *featureGenerator, labelListList, options.numThreads);
}

void SegmenterClass::readModel(const string &modelFilename) {
    CRFProcessor = make_shared<HighOrderCRFProcessor<CharWithSpace>>();
    CRFProcessor->readModel(modelFilename);
}

}  // namespace Segmenter

int main(int argc, char **argv) {
    return Segmenter::mainProc(argc, argv);
}
