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

#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
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
using std::queue;
using std::shared_ptr;
using std::string;
using std::stringstream;
using std::unordered_set;
using std::vector;

vector<string> splitStringBySpace(const string &s) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, ' ')) {
        elems.push_back(item);
    }
    return elems;
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

    auto wordAndLabelList = splitStringBySpace(line);
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
            vector<string> labels = dictionary->lookup(wordAndLabel[0]);
            if (!labels.empty()) {
                possibleLabelSet.insert(labels.begin(), labels.end());
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

shared_ptr<unordered_set<string>> readTagSet(const string &filename) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cerr << "Cannot read from the tag set file: " << filename << endl;
        exit(1);
    }
    
    auto ret = make_shared<unordered_set<string>>();
    string line;
    while (getline(ifs, line)) {
        ret->insert(line);
    }
    ifs.close();
    return ret;
}


enum optionIndex { UNKNOWN, HELP, TRAIN, TAG, UNK, TAGSET, TEST, MODEL, DICT, THREADS };

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
    { TAG, 0, "", "tag", Arg::None, "  --tag  \tTags the text read from the standard input and writes the result to the standard output. This option can be omitted." },
    { TAGSET, 0, "", "tagset", Arg::Required, "  --tagset  <file>\tDesignates the tag set. Only valid for training." },
    { TEST, 0, "", "test", Arg::Required, "  --test  <file>\tTests the model with the given file." },
    { TRAIN, 0, "", "train", Arg::Required, "  --train  <file>\tTrains the model on the given file." },
    { THREADS, 0, "", "threads", Arg::Required, "  --threads  <number>\tDesignates the number of threads to run concurrently." },
    { UNK, 0, "", "unk", Arg::None, "  --unk  \tAdds a question mark to the tags of unknown words. Only valid for tagging." },
    { UNKNOWN, 0, "", "", Arg::None, "Examples:\n"
    "  Tagger --train train.txt --model model.dat\n"
    "  Tagger --test test.txt --model model.dat\n"
    "  Tagger --segment < input_file > output_file"
    },
    { 0, 0, 0, 0, 0, 0 }
};

int mainProc(int argc, char **argv) {
    Tagger::TaggerOptions op = { 2, 2, 4, 1, "" };

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
            cerr << "Illegal number of threads." << endl;
            exit(1);
        }
        op.numThreads = num;
    }
        
    if (options[TRAIN]) {
        if (!options[TAGSET]) {
            cerr << "Tag set was not designated." << endl;
        }
        auto tagSet = Tagger::readTagSet(options[TAGSET].arg);
        string trainingFilename = options[TRAIN].arg;
        Tagger::TaggerClass s(op);
        s.train(trainingFilename, modelFilename, tagSet);
        return 0;
    }

    if (options[TEST]) {
        string testFilename = options[TEST].arg;
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
        future<string> f = tq.enqueue(&Tagger::TaggerClass::tag, &s, line, options[UNK]);
        futureQueue.push(move(f));
        while (!futureQueue.empty() && futureQueue.front().wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            cout << futureQueue.front().get() << endl;
            futureQueue.pop();
        }
    }
    while (!futureQueue.empty()) {
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
        dictionary = make_shared<DictionaryClass>(options.dictionaryFilename, false);
        gen->addFeatureTemplateGenerator(make_shared<DictionaryFeatureGenerator>(dictionary));
    }
    featureGenerator = gen;
};

shared_ptr<vector<shared_ptr<ObservationSequence<string>>>> TaggerClass::readData(const string &fileName, bool hasValidLabels) {
    ifstream ifs(fileName);
    if (!ifs.is_open()) {
        cerr << "Cannot read from file: " << fileName << endl;
        exit(1);
    }
    auto observationSequenceList = make_shared<vector<shared_ptr<ObservationSequence<string>>>>();
    string line;
    while (getline(ifs, line)) {
        observationSequenceList->push_back(convertLineToObservationSequence(line, dictionary, hasValidLabels));
    }
    ifs.close();
    return observationSequenceList;
}

void TaggerClass::train(const string &trainingFilename,
                        const string &modelFilename,
                        shared_ptr<unordered_set<string>> tagSet) {
    auto observationSequenceList = readData(trainingFilename, true);
    CRFProcessor = make_shared<HighOrderCRFProcessor<string>>();
    CRFProcessor->train(observationSequenceList, featureGenerator, tagSet, options.numThreads, 10000, false, 10.0, 0.00001);
    CRFProcessor->writeModel(modelFilename);
}

string TaggerClass::tag(string line, bool tagUnknown) const {
    auto observationSequence = convertLineToObservationSequence(line, dictionary, false);
    auto tagList = CRFProcessor->tag(observationSequence, featureGenerator);
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
        if (i < wordList->size() - 1) {
            ret += ' ';
        }
    }
    return ret;
}

void TaggerClass::test(const string &testFilename) {
    auto observationSequenceList = readData(testFilename, true);
    auto labelListList = make_shared<vector<shared_ptr<vector<string>>>>();
    for (auto &observationSequence : *observationSequenceList) {
        labelListList->push_back(observationSequence->getLabelList());
    }
    CRFProcessor->test(observationSequenceList, featureGenerator, labelListList, options.numThreads);
}

void TaggerClass::readModel(const string &modelFilename) {
    CRFProcessor = make_shared<HighOrderCRFProcessor<string>>();
    CRFProcessor->readModel(modelFilename);
}


}  // namespace Tagger

int main(int argc, char **argv) {
    return Tagger::mainProc(argc, argv);
}

