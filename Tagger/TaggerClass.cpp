#include "TaggerClass.h"

#include "../Dictionary/DictionaryClass.h"
#include "../HighOrderCRF/AggregatedFeatureTemplateGenerator.h"
#include "../HighOrderCRF/HighOrderCRFProcessor.h"
#include "../HighOrderCRF/ObservationSequence.h"
#include "../HighOrderCRF/UnconditionalFeatureTemplateGenerator.h"
#include "../task/task_queue.hpp"
#include "../optionparser/optionparser.h"
#include "DictionaryFeatureGenerator.h"
#include "TaggerOptions.h"
#include "WordFeatureGenerator.h"

#include <cassert>
#include <chrono>
#include <cstdio>
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

namespace Tagger {

using Dictionary::DictionaryClass;
using HighOrderCRF::AggregatedFeatureTemplateGenerator;
using HighOrderCRF::HighOrderCRFProcessor;
using HighOrderCRF::ObservationSequence;
using HighOrderCRF::UnconditionalFeatureTemplateGenerator;

using std::cin;
using std::endl;
using std::cout;
using std::cerr;
using std::future;
using std::getline;
using std::ifstream;
using std::make_shared;
using std::move;
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

static vector<string> splitStringBySpaces(const string &s) {
    return splitString(s, ' ');
}

static vector<string> splitStringByTabs(const string &s) {
    return splitString(s, '\t');
}

vector<string> rsplit2BySlash(const string &s) {
    vector<string> elems;
    size_t pos = s.rfind('/');
    elems.push_back(s.substr(0, pos));
    if (pos != string::npos) {
        elems.push_back(s.substr(pos + 1));
    }
    return elems;
}

shared_ptr<ObservationSequence<string>> convertLineToObservationSequence(const string &line, shared_ptr<DictionaryClass> dictionary, bool hasValidLabels) {
    auto observationList = make_shared<vector<string>>();
    auto labelList = make_shared<vector<string>>();
    auto possibleLabelSetList = make_shared<vector<unordered_set<string>>>();

    auto wordAndLabelList = splitStringBySpaces(line);
    for (const auto &wordAndLabelStr : wordAndLabelList) {
        auto wordAndLabel = rsplit2BySlash(wordAndLabelStr);
        string &word = wordAndLabel[0];
        if (hasValidLabels) {
            if (wordAndLabel.size() != 2) {
                cerr << "Not properly tagged: " << wordAndLabelStr << endl;
                exit(1);
            }
        }
        
        unordered_set<string> possibleLabelSet;
        if (dictionary) {
            vector<vector<const string *>> labelListList = dictionary->lookup(wordAndLabel[0]);
            if (!labelListList.empty()) {
                for (const auto &labelList : labelListList) {
                    assert(labelList.size() == 1);
                    possibleLabelSet.insert(*labelList[0]);
                }
                if (hasValidLabels) {
                    possibleLabelSet.insert(wordAndLabel[1]);
                }
            }
        }
        possibleLabelSetList->push_back(move(possibleLabelSet));
        if (hasValidLabels) {
            labelList->push_back(move(wordAndLabel[1]));
        }
        
        observationList->push_back(move(wordAndLabel[0]));
    }

    return make_shared<ObservationSequence<string>>(observationList, labelList, possibleLabelSetList, hasValidLabels);
}

unordered_set<string> readTagSet(const string &filename) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cerr << "Cannot read from the tag set file: " << filename << endl;
        exit(1);
    }
    
    unordered_set<string> ret;
    string line;
    while (getline(ifs, line)) {
        ret.insert(line);
    }
    ifs.close();
    return ret;
}


enum optionIndex { UNKNOWN, HELP, TRAIN, TAG, NEWLINE, UNK, TAGSET, TEST, MODEL, DICT, THREADS, WORD_N, WORD_W, WORD_L, REGTYPE, COEFF, EPSILON, MAXITER };
vector<string> optionsToSave { "WORD_N", "WORD_W", "WORD_L" };

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
    { TAG, "TAG", 0, "", "tag", Arg::None, "  --tag  \tTags the text read from the standard input and writes the result to the standard output. This option can be omitted." },
    { NEWLINE, "NEWLINE", 0, "", "newline", Arg::None, "  --newline  \tOutputs newline-separated tags. Valid only with --tag option. Use this option to feed the morpheme tagger." },
    { WORD_N, "WORD_N", 0, "", "wordn", Arg::Required, "  --wordn  <number>\tN-gram length of words. Defaults to 2." },
    { WORD_W, "WORD_W", 0, "", "wordw", Arg::Required, "  --wordw  <number>\tWindow width for words. Defaults to 2." },
    { WORD_L, "WORD_L", 0, "", "wordl", Arg::Required, "  --wordl  <number>\tMaximum label length of words. Defaults to 4." },
    { TAGSET, "TAGSET", 0, "", "tagset", Arg::Required, "  --tagset  <file>\tDesignates the tag set. Only valid for training." },
    { TEST, "TEST", 0, "", "test", Arg::Required, "  --test  <file>\tTests the model with the given file." },
    { TRAIN, "TRAIN", 0, "", "train", Arg::Required, "  --train  <file>\tTrains the model on the given file." },
    { REGTYPE, "REGTYPE", 0, "", "regtype", Arg::Required, "  --regtype  <type>\tDesignates the regularization type (\"L1\" / \"L2\") for optimization." },
    { COEFF, "COEFF", 0, "", "coeff", Arg::Required, "  --coeff  <number>\tSets the regularization coefficient." },
    { EPSILON, "EPSILON", 0, "", "epsilon", Arg::Required, "  --epsilon  <number>\tSets the epsilon for convergence." },
    { MAXITER, "MAXITER", 0, "", "maxiter", Arg::Required, "  --maxiter  <number>\tSets the maximum iteration count." },
    { THREADS, "THREADS", 0, "", "threads", Arg::Required, "  --threads  <number>\tDesignates the number of threads to run concurrently." },
    { UNK, "UNK", 0, "", "unk", Arg::None, "  --unk  \tAdds a question mark to the tags of unknown words. Only valid for tagging." },
    { UNKNOWN, "UNKNOWN", 0, "", "", Arg::None, "Examples:\n"
    "  Tagger --train train.txt --model model.dat\n"
    "  Tagger --test test.txt --model model.dat\n"
    "  Tagger --segment < input_file > output_file"
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
    argv += (argc > 0);
    argc -= (argc > 0);

    option::Stats stats(usage, argc, argv);
    vector<option::Option> options(stats.options_max);
    vector<option::Option> buffer(stats.buffer_max);
    option::Parser parse(usage, argc, argv, options.data(), buffer.data());

    if (parse.error()) {
        return 1;
    }

    unordered_map<string, string> optionMap = {
        {"WORD_N", "2"},
        {"WORD_W", "2"},
        {"WORD_L", "4"},
    };

    for (auto &option : options) {
        if (option.count() > 0) {
            optionMap[option.desc->name] = (option.arg ? option.arg : "");
        }
    }

    if (optionMap.find("HELP") != optionMap.end()) {
        option::printUsage(cout, usage);
        return 0;
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
        
    if (optionMap.find("WORD_N") != optionMap.end()) {
        op.wordMaxNgram = atoi(optionMap["WORD_N"].c_str());
    }
    if (optionMap.find("WORD_W") != optionMap.end()) {
        op.wordMaxWindow = atoi(optionMap["WORD_W"].c_str());
    }
    if (optionMap.find("WORD_L") != optionMap.end()) {
        op.wordMaxLabelLength = atoi(optionMap["WORD_L"].c_str());
    }
        
    if (optionMap.find("TRAIN") != optionMap.end()) {
        if (optionMap.find("TAGSET") == optionMap.end()) {
            cerr << "Tag set was not designated." << endl;
        }
        auto tagSet = Tagger::readTagSet(optionMap["TAGSET"]);
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

        Tagger::TaggerClass s(op);
        s.train(trainingFilename, modelFilename, tagSet);

        string optionFilename = modelFilename + ".options";
        writeOptions(optionFilename, optionsToSave, optionMap);

        return 0;
    }

    if (optionMap.find("TEST") != optionMap.end()) {
        string testFilename = optionMap["TEST"];
        Tagger::TaggerClass s(op);
        s.readModel(modelFilename);
        s.test(testFilename);
        return 0;
    }

    // tags the inputs
    Tagger::TaggerClass s(op);
    s.readModel(modelFilename);
    
    string line;
    hwm::task_queue tq(op.numThreads);
    queue<future<string>> futureQueue;
    
    while (getline(cin, line)) {
        future<string> f = tq.enqueue(&Tagger::TaggerClass::tag, &s, line, optionMap.find("UNK") != optionMap.end(), optionMap.find("NEWLINE") != optionMap.end());
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

TaggerClass::TaggerClass(const TaggerOptions &options) {
    this->options = options;
    auto gen = make_shared<AggregatedFeatureTemplateGenerator<string>>();
    gen->addFeatureTemplateGenerator(make_shared<UnconditionalFeatureTemplateGenerator<string>>(2));
    gen->addFeatureTemplateGenerator(make_shared<WordFeatureGenerator>(options.wordMaxNgram,
                                                                       options.wordMaxWindow,
                                                                       options.wordMaxLabelLength));
    if (!options.dictionaryFilename.empty()) {
        dictionary = make_shared<DictionaryClass>(options.dictionaryFilename);
        gen->addFeatureTemplateGenerator(make_shared<DictionaryFeatureGenerator>(dictionary));
    }
    featureGenerator = gen;
};

vector<shared_ptr<ObservationSequence<string>>> TaggerClass::readData(const string &fileName, bool hasValidLabels) {
    ifstream ifs(fileName);
    if (!ifs.is_open()) {
        cerr << "Cannot read from file: " << fileName << endl;
        exit(1);
    }
    vector<shared_ptr<ObservationSequence<string>>> observationSequenceList;
    string line;
    while (getline(ifs, line)) {
        observationSequenceList.push_back(convertLineToObservationSequence(line, dictionary, hasValidLabels));
    }
    ifs.close();
    return observationSequenceList;
}

void TaggerClass::train(const string &trainingFilename,
                        const string &modelFilename,
                        const unordered_set<string> &tagSet) {
    auto observationSequenceList = readData(trainingFilename, true);
    bool isL1 = false;
    if (!options.regType.empty() && options.regType != "L1" && options.regType != "L2") {
        cerr << "Unsupported regularization type: " << options.regType;
    }
    isL1 = (options.regType == "L1");
    CRFProcessor = make_shared<HighOrderCRFProcessor<string>>();
    CRFProcessor->train(observationSequenceList, *featureGenerator, tagSet, options.numThreads, options.maxIter, isL1, options.coeff, options.epsilon);
    CRFProcessor->writeModel(modelFilename);
}

string TaggerClass::tag(string line, bool tagUnknown, bool delimitByNewline) const {
    if (line.empty()) {
        return "";
    }
    auto observationSequence = convertLineToObservationSequence(line, dictionary, false);
    auto tagList = CRFProcessor->tag(*observationSequence, *featureGenerator);
    auto wordList = observationSequence->getObservationList();
    auto possibleLabelSetList = observationSequence->getPossibleLabelSetList();
    string ret;
    for (size_t i = 0; i < wordList->size(); ++i) {
        ret += (*wordList)[i];
        ret += '/';
        ret += (*tagList)[i];
        if (tagUnknown && (*possibleLabelSetList)[i].empty()) {
            ret += '?';
        }
        if (delimitByNewline) {
            ret += '\n';
        }
        else if (i < wordList->size() - 1) {
            ret += ' ';
        }
    }
    return ret;
}

void TaggerClass::test(const string &testFilename) {
    auto observationSequenceList = readData(testFilename, true);
    vector<shared_ptr<vector<string>>> labelListList;
    for (auto &observationSequence : observationSequenceList) {
        labelListList.push_back(observationSequence->getLabelList());
    }
    CRFProcessor->test(observationSequenceList, *featureGenerator, labelListList, options.numThreads);
}

void TaggerClass::readModel(const string &modelFilename) {
    CRFProcessor = make_shared<HighOrderCRFProcessor<string>>();
    CRFProcessor->readModel(modelFilename);
}


}  // namespace Tagger

int main(int argc, char **argv) {
    return Tagger::mainProc(argc, argv);
}

