#include "SegmenterClass.h"

#include "../HighOrderCRF/AggregatedFeatureTemplateGenerator.h"
#include "../HighOrderCRF/HighOrderCRFProcessor.h"
#include "../HighOrderCRF/ObservationSequence.h"
#include "../HighOrderCRF/UnconditionalFeatureTemplateGenerator.h"
#include "../task/task_queue.hpp"
#include "CharacterFeatureGenerator.h"
#include "CharacterTypeFeatureGenerator.h"
#include "DictionaryFeatureGenerator.h"
#include "../optionparser/optionparser.h"
#include "SegmenterOptions.h"
#include "UnicodeCharacter.h"

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
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
using std::queue;
using std::shared_ptr;
using std::string;
using std::unordered_set;
using std::vector;

shared_ptr<ObservationSequence<UnicodeCharacter>> convertLineToObservationSequence(const string &line, bool hasValidLabels) {
    const char *buf = line.c_str();
    size_t len = line.size();
    bool prevIsSpace = true;
    auto observationList = make_shared<vector<UnicodeCharacter>>();
    auto labelList = make_shared<vector<string>>();

    size_t pos = 0;
    bool isAfterSlash = false;
    while (pos < len) {
        size_t charCount = 0;
        auto uchar = UnicodeCharacter::fromString(buf + pos, len, &charCount);
        pos += charCount;
        if (uchar.getCodePoint() == ' ') {
            prevIsSpace = true;
            continue;
        }
        else {
            observationList->push_back(uchar);
            labelList->push_back(prevIsSpace ? "1" : "0");
            prevIsSpace = false;
        }
    }
    auto possibleLabelSetList = make_shared<vector<unordered_set<string>>>(observationList->size());
    for (size_t i = 0; i < possibleLabelSetList->size(); ++i) {
        (*possibleLabelSetList)[i].insert("1");
        if (i > 0) {
            (*possibleLabelSetList)[i].insert("0");
        }
    }
    return make_shared<ObservationSequence<UnicodeCharacter>>(observationList, labelList, possibleLabelSetList, hasValidLabels);
}


enum optionIndex { UNKNOWN, HELP, TRAIN, SEGMENT, TEST, MODEL, DICT, THREADS, CHAR_N, CHAR_W, CHAR_L, TYPE_N, TYPE_W, TYPE_L, REGTYPE, COEFF, EPSILON, MAXITER };

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
    { UNKNOWN, 0, "", "", Arg::None, "USAGE:  [options]\n\n"
    "Options:" },
    { HELP, 0, "h", "help", Arg::None, "  -h, --help  \tPrints usage and exit." },
    { MODEL, 0, "", "model", Arg::Required, "  --model  <file>\tDesignates the model file to be saved/loaded." },
    { DICT, 0, "", "dict", Arg::Required, "  --dict  <file>\tDesignates the dictionary file to be loaded." },
    { CHAR_N, 0, "", "charn", Arg::Required, "  --charn  <number>\tN-gram length of characters." },
    { CHAR_W, 0, "", "charw", Arg::Required, "  --charw  <number>\tWindow width for characters." },
    { CHAR_L, 0, "", "charl", Arg::Required, "  --charl  <number>\tMaximum label length of characters." },
    { TYPE_N, 0, "", "typen", Arg::Required, "  --typen  <number>\tN-gram length of character types." },
    { TYPE_W, 0, "", "typew", Arg::Required, "  --typew  <number>\tWindow width for character types." },
    { TYPE_L, 0, "", "typel", Arg::Required, "  --typel  <number>\tMaximum label length of character types." },
    { SEGMENT, 0, "", "segment", Arg::None, "  --segment  \tSegments text read from the standard input and writes the result to the standard output. This option can be omitted." },
    { TEST, 0, "", "test", Arg::Required, "  --test  <file>\tTests the model with the given file." },
    { TRAIN, 0, "", "train", Arg::Required, "  --train  <file>\tTrains the model on the given file." },
    { REGTYPE, 0, "", "regtype", Arg::Required, "  --regtype  <type>\tDesignates the regularization type (\"L1\" / \"L2\") for optimization." },
    { COEFF, 0, "", "coeff", Arg::Required, "  --coeff  <number>\tSets the regularization coefficient." },
    { EPSILON, 0, "", "epsilon", Arg::Required, "  --epsilon  <number>\tSets the epsilon for convergence." },
    { MAXITER, 0, "", "maxiter", Arg::Required, "  --maxiter  <number>\tSets the maximum iteration count." },
    { THREADS, 0, "", "threads", Arg::Required, "  --threads  <number>\tDesignates the number of threads to run concurrently." },
    { UNKNOWN, 0, "", "", Arg::None, "Examples:\n"
    "  Segmenter --train train.txt --model model.dat\n"
    "  Segmenter --test test.txt --model model.dat\n"
    "  Segmenter --segment < input_file > output_file"
    },
    { 0, 0, 0, 0, 0, 0 }
};


int mainProc(int argc, char **argv) {
    Segmenter::SegmenterOptions op = { 3, 3, 4, 3, 3, 1, 1 };

    argv += (argc > 0);
    argc -= (argc > 0);

    option::Stats stats(usage, argc, argv);
    vector<option::Option> options(stats.options_max);
    vector<option::Option> buffer(stats.buffer_max);
    option::Parser parse(usage, argc, argv, options.data(), buffer.data());

    if (parse.error()) {
        return 1;
    }

    if (options[HELP]) {
        option::printUsage(cout, usage);
        return 0;
    }

    string modelFilename;
    if (options[MODEL]) {
        modelFilename = options[MODEL].arg;
    }
    else {
        option::printUsage(cerr, usage);
        return 0;
    }

    string dictFilename;
    if (options[DICT]) {
        dictFilename = options[DICT].arg;
        op.dictionaryFilename = dictFilename;
    }

    op.numThreads = 1;
    if (options[THREADS]) {
        char* endptr;
        int num = strtol(options[THREADS].arg, &endptr, 10);
        if (endptr == options[THREADS].arg || *endptr != 0 || num < 1) {
            cerr << "Illegal number of threads" << endl;
            exit(1);
        }
        op.numThreads = num;
    }

    if (options[CHAR_N]) {
        op.charMaxNgram = atoi(options[CHAR_N].arg);
    }
    if (options[CHAR_W]) {
        op.charMaxWindow = atoi(options[CHAR_W].arg);
    }
    if (options[CHAR_L]) {
        op.charMaxLabelLength = atoi(options[CHAR_L].arg);
    }
    if (options[TYPE_N]) {
        op.charMaxNgram = atoi(options[TYPE_N].arg);
    }
    if (options[TYPE_W]) {
        op.charMaxWindow = atoi(options[TYPE_W].arg);
    }
    if (options[TYPE_L]) {
        op.charMaxLabelLength = atoi(options[TYPE_L].arg);
    }
        
    if (options[TRAIN]) {
        string trainingFilename = options[TRAIN].arg;

        if (options[COEFF]) {
            op.coeff = atof(options[COEFF].arg);
        }
        if (options[EPSILON]) {
            op.epsilon = atof(options[EPSILON].arg);
        }
        if (options[MAXITER]) {
            op.epsilon = atoi(options[MAXITER].arg);
        }
        if (options[REGTYPE]) {
            op.regType = options[REGTYPE].arg;
        }

        Segmenter::SegmenterClass s(op);
        s.train(trainingFilename, modelFilename);
        return 0;
    }

    if (options[TEST]) {
        string testFilename = options[TEST].arg;
        Segmenter::SegmenterClass s(op);
        s.readModel(modelFilename);
        s.test(testFilename);
        return 0;
    }

    // segments the inputs
    Segmenter::SegmenterClass s(op);
    s.readModel(modelFilename);
    
    string line;
    hwm::task_queue tq(op.numThreads);
    queue<future<string>> futureQueue;
    
    while (getline(cin, line)) {
        future<string> f = tq.enqueue(&Segmenter::SegmenterClass::segment, s, line);
        futureQueue.push(move(f));
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
    auto gen = make_shared<AggregatedFeatureTemplateGenerator<UnicodeCharacter>>();
    gen->addFeatureTemplateGenerator(make_shared<UnconditionalFeatureTemplateGenerator<UnicodeCharacter>>(1));
    gen->addFeatureTemplateGenerator(make_shared<CharacterFeatureGenerator>(options.charMaxNgram,
                                                                            options.charMaxWindow,
                                                                            options.charMaxLabelLength));
    gen->addFeatureTemplateGenerator(make_shared<CharacterTypeFeatureGenerator>(options.charTypeMaxNgram,
                                                                                options.charTypeMaxWindow,
                                                                                options.charTypeMaxLabelLength));
    if (!options.dictionaryFilename.empty()) {
        gen->addFeatureTemplateGenerator(make_shared<DictionaryFeatureGenerator>(options.dictionaryFilename));
    }
    featureGenerator = gen;
};

vector<shared_ptr<ObservationSequence<UnicodeCharacter>>> SegmenterClass::readData(const string &fileName, bool hasValidLabels) {
    ifstream ifs(fileName);
    if (!ifs.is_open()) {
        cerr << "Cannot read from file: " << fileName << endl;
        exit(1);
    }
    vector<shared_ptr<ObservationSequence<UnicodeCharacter>>> observationSequenceList;
    string line;
    while (getline(ifs, line)) {
        observationSequenceList.push_back(convertLineToObservationSequence(line, hasValidLabels));
    }
    ifs.close();
    return observationSequenceList;
}

void SegmenterClass::train(const string &trainingFilename,
                           const string &modelFilename) {
    auto observationSequenceList = readData(trainingFilename, true);
    CRFProcessor = make_shared<HighOrderCRFProcessor<UnicodeCharacter>>();
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
    auto observationSequence = convertLineToObservationSequence(line, false);
    auto spaceList = CRFProcessor->tag(*observationSequence, *featureGenerator);
    auto unicodeList = observationSequence->getObservationList();
    string ret;
    for (size_t i = 0; i < unicodeList->size(); ++i) {
        if (i > 0 && (*spaceList)[i] == "1") {
            ret += " ";
        }
        ret += (*unicodeList)[i].toString();
    }
    return ret;
}

void SegmenterClass::test(const string &testFilename) {
    auto observationSequenceList = readData(testFilename, true);
    vector<shared_ptr<vector<string>>> labelListList;
    for (auto &observationSequence : observationSequenceList) {
        labelListList.push_back(observationSequence->getLabelList());
    }
    CRFProcessor->test(observationSequenceList, *featureGenerator, labelListList, options.numThreads);
}

void SegmenterClass::readModel(const string &modelFilename) {
    CRFProcessor = make_shared<HighOrderCRFProcessor<UnicodeCharacter>>();
    CRFProcessor->readModel(modelFilename);
}

}  // namespace Segmenter

int main(int argc, char **argv) {
    return Segmenter::mainProc(argc, argv);
}
