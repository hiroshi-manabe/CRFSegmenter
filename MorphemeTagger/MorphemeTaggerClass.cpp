#include "MorphemeTaggerClass.h"

#include "../MaxEnt/MaxEntProcessor.h"
#include "../task/task_queue.hpp"
#include "../optionparser/optionparser.h"
#include "Dictionary.h"
#include "MorphemeTaggerOptions.h"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <istream>
#include <memory>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace MorphemeTagger {

using MaxEnt::MaxEntProcessor;
using MaxEnt::Observation;

using std::back_inserter;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::equal;
using std::future;
using std::getline;
using std::ifstream;
using std::istream;
using std::make_shared;
using std::move;
using std::ofstream;
using std::queue;
using std::set;
using std::shared_ptr;
using std::showpos;
using std::string;
using std::stringstream;
using std::unordered_set;
using std::vector;

static vector<string> splitStringByTabs(const string &s) {
    vector<string> elems;
    size_t pos;
    size_t lastPos = 0;
    while (true) {
        pos = s.find_first_of('\t', lastPos);
        if (pos == string::npos) {
            pos = s.length();
            elems.push_back(string(s.begin() + lastPos, s.begin() + pos));
            break;
        }
        else {
            elems.push_back(string(s.begin() + lastPos, s.begin() + pos));
        }
        lastPos = pos + 1;
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

vector<shared_ptr<vector<vector<string>>>> lookupSentence(const vector<string> &sentence, const Dictionary &dictionary) {
    vector<shared_ptr<vector<vector<string>>>> ret;
    for (const auto &str : sentence) {
        ret.push_back(dictionary.lookup(str));
    }
    return ret;
}

vector<unordered_set<string>> convertSentenceToCommonAttributeSetList(const vector<string> &sentence, const vector<shared_ptr<vector<vector<string>>>> &dictResultListList, const MorphemeTaggerOptions &opt) {
    assert(sentence.size() == dictResultListList.size());
    vector<vector<string>> wordAndLabelList;
    
    for (const auto &wordAndLabelStr : sentence) {
        auto wordAndLabel = rsplit2BySlash(wordAndLabelStr);
        wordAndLabelList.push_back(move(wordAndLabel));
    }
    
    vector<unordered_set<string>> ret(sentence.size());
    for (size_t i = 0; i < sentence.size(); ++i) {
        unordered_set<string> commonAttributeSet;
        if (dictResultListList[i]->size() < 2) {
            continue;
        }
        
        for (int j = -(int)opt.columnMaxWindow; j <= (int)opt.columnMaxWindow; ++j) {
            int pos = i + j;
            if (j == 0 || pos < 0 || pos >= (int)sentence.size()) {
                continue;
            }
            if (dictResultListList[pos]->empty()) {
                continue;
            }
            stringstream posPrefix;
            posPrefix << "P" << showpos << j << "-";
            for (const auto &dictResult : *dictResultListList[pos]) {
                for (size_t k = 0; k < dictResult.size(); ++k) {
                    if (opt.featureColumnSet.find(k) == opt.featureColumnSet.end()) {
                        continue;
                    }
                    stringstream fieldPrefix;
                    fieldPrefix << "F" << k << ":";
                    commonAttributeSet.insert(fieldPrefix.str() + dictResult[k]);
//                    commonAttributeSet.insert(posPrefix.str() + fieldPrefix.str() + dictResult[k]);
                }
            }
        }
        
        for (int wordOrLabel : {0, 1}) {
            for (int sign : { -1, +1 }) {
                for (int startOffset : {0, 1}) {
                    stringstream ss;
                    for (int j = startOffset; j <= (int)(wordOrLabel == 0 ? opt.wordMaxWindow : opt.labelMaxWindow); ++j) {
                        int startPos = i + (sign * startOffset);
                        if (j == 0 && sign == -1) {
                            continue;
                        }
                        int pos = i + j * sign;
                        if (pos < 0 || pos >= (int)sentence.size()) {
                            continue;
                        }
                        ss << (j == startOffset ? ":" : "-") << wordAndLabelList[pos][wordOrLabel];
                        stringstream attr;
                        attr << (wordOrLabel == 0 ? "W" : "L") << (sign == -1 ? "-" : "+") << startOffset << "-" << j << ss.str();
                        commonAttributeSet.insert(attr.str());
                    }
                }
            }
        }
        ret[i] = move(commonAttributeSet);
    }

    return ret;
}

vector<Observation> generateTrainingObservationList(const vector<vector<string>> &dictResultList, const unordered_set<string>& commonAttributeSet, const vector<string> &correctResult) {
    vector<Observation> ret;
    if (dictResultList.size() < 2 || correctResult.empty()) {
        return ret;
    }

    unordered_set<size_t> survivors;
    for (size_t i = 0; i < dictResultList.size(); ++i) {
        survivors.insert(i);
    }
    unordered_set<string> attributeSet(commonAttributeSet);
    for (size_t i = 0; i < correctResult.size(); ++i) {
        unordered_set<size_t> nextSurvivors;
        for (size_t j : survivors) {
            if (dictResultList[j][i] == correctResult[i]) {
                nextSurvivors.insert(j);
            }
        }
        if (nextSurvivors.empty()) {
            break;
        }
        stringstream ss;
        ss << "E" << i << ":";
        string prefix(ss.str());
        if (nextSurvivors.size() < survivors.size()) {
            set<string> possibleLabelSet;
            for (size_t j : survivors) {
                stringstream ss;
                possibleLabelSet.insert(prefix + dictResultList[j][i]);
            }
            ret.emplace_back(attributeSet, prefix + correctResult[i], move(possibleLabelSet));
            survivors = nextSurvivors;
            if (survivors.size() == 1) {
                break;
            }
        }
        attributeSet.insert(prefix + correctResult[i]);
    }
    return ret;
}

size_t inferCorrectResult(const vector<vector<string>> &dictResultList, const unordered_set<string> &commonAttributeSet, const MaxEntProcessor &maxEntProcessor) {
    if (dictResultList.size() < 2) {
        return 0;
    }
    unordered_set<size_t> survivors;
    for (size_t i = 0; i < dictResultList.size(); ++i) {
        survivors.insert(i);
    }
    unordered_set<string> attributeSet(commonAttributeSet);
    for (size_t i = 0; i < dictResultList[0].size(); ++i) {
        set<string> possibleLabelSet;
        stringstream ss;
        ss << "E" << i << ":";
        string prefix(ss.str());
        for (size_t j : survivors) {
            possibleLabelSet.insert(prefix + dictResultList[j][i]);
        }
        if (possibleLabelSet.size() > 1) {
            const vector<string> &result = dictResultList[*(survivors.begin())];
            string inferredLabel = maxEntProcessor.inferLabel(Observation(attributeSet, string(), move(possibleLabelSet)));
            unordered_set<size_t> nextSurvivors;
            for (size_t j : survivors) {
                if (prefix + dictResultList[j][i] == inferredLabel) {
                    nextSurvivors.insert(j);
                }
            }
            if (nextSurvivors.empty()) {
                break;
            }
            survivors = nextSurvivors;
            if (survivors.size() == 1) {
                break;
            }
        }
        attributeSet.insert(prefix + dictResultList[*(survivors.begin())][i]);
    }
    return *(survivors.begin());
}

void readSentence(istream *is, vector<string> *sentence, vector<vector<string>> *correctResultList, bool hasCorrectResults) {
    string line;
    while (getline(*is, line)) {
        if (line.empty()) {
            break;
        }
        vector<string> elems = splitStringByTabs(line);
        if (elems.size() < (size_t)(hasCorrectResults ? 2 : 1)) {
            cerr << "Not properly tagged: " << line << endl;
        }
        sentence->push_back(elems[0]);
        correctResultList->emplace_back(elems.begin() + 1, elems.end());
    }
}


enum optionIndex { UNKNOWN, HELP, TRAIN, TAG, TEST, MODEL, DICT, THREADS, WORD_W, LABEL_W, COLUMN_W, FCOLUMN, REGTYPE, COEFF, EPSILON, MAXITER };

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
    { WORD_W, 0, "", "wordw", Arg::Required, "  --wordw  <number>\tWindow width for words." },
    { LABEL_W, 0, "", "labelw", Arg::Required, "  --labelw  <number>\tWindow width for words." },
    { COLUMN_W, 0, "", "columnw", Arg::Required, "  --columnw  <number>\tWindow width for columns." },
    { FCOLUMN, 0, "", "fcolumn", Arg::Required, "  --fcolumn  <number> [number ...]\tDesignates the columns to use as features." },
    { TAG, 0, "", "tag", Arg::None, "  --tag  \tTags the text read from the standard input and writes the result to the standard output. This option can be omitted." },
    { TEST, 0, "", "test", Arg::Required, "  --test  <file>\tTests the model with the given file." },
    { TRAIN, 0, "", "train", Arg::Required, "  --train  <file>\tTrains the model on the given file." },
    { REGTYPE, 0, "", "regtype", Arg::Required, "  --regtype  <type>\tDesignates the regularization type (\"L1\" / \"L2\") for optimization." },
    { COEFF, 0, "", "coeff", Arg::Required, "  --coeff  <number>\tSets the regularization coefficient." },
    { EPSILON, 0, "", "epsilon", Arg::Required, "  --epsilon  <number>\tSets the epsilon for convergence." },
    { MAXITER, 0, "", "maxiter", Arg::Required, "  --maxiter  <number>\tSets the maximum iteration count." },
    { THREADS, 0, "", "threads", Arg::Required, "  --threads  <number>\tDesignates the number of threads to run concurrently." },
    { UNKNOWN, 0, "", "", Arg::None, "Examples:\n"
    "  MorphemeTagger --train train.txt --model model.dat\n"
    "  MorphemeTagger --test test.txt --model model.dat\n"
    "  MorphemeTagger --segment < input_file > output_file"
    },
    { 0, 0, 0, 0, 0, 0 }
};

int mainProc(int argc, char **argv) {
    MorphemeTagger::MorphemeTaggerOptions op = { 2, 1, 1, 1 };

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
        

    if (options[WORD_W]) {
        op.wordMaxWindow = atoi(options[WORD_W].arg);
    }
    if (options[LABEL_W]) {
        op.labelMaxWindow = atoi(options[LABEL_W].arg);
    }
    if (options[COLUMN_W]) {
        op.columnMaxWindow = atoi(options[COLUMN_W].arg);
    }
    for (option::Option* opt = options[FCOLUMN]; opt; opt = opt->next()) {
        op.featureColumnSet.insert((size_t)atoi(opt->arg));
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
        
        MorphemeTagger::MorphemeTaggerClass s(op);

        s.train(trainingFilename, modelFilename);
        return 0;
    }

    if (options[TEST]) {
        string testFilename = options[TEST].arg;
        MorphemeTagger::MorphemeTaggerClass s(op);
        s.readModel(modelFilename);
        s.test(testFilename);
        return 0;
    }

    // tags the inputs
    MorphemeTagger::MorphemeTaggerClass s(op);
    s.readModel(modelFilename);
    
    string line;
    hwm::task_queue tq(op.numThreads);
    queue<future<vector<vector<string>>>> futureQueue;

    vector<string> sentence;
    while (getline(cin, line)) {
        if (line.empty()) {
            auto f = tq.enqueue(&MorphemeTagger::MorphemeTaggerClass::tag, &s, sentence);
            futureQueue.push(move(f));
            while (!futureQueue.empty() && futureQueue.front().wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                const auto result = futureQueue.front().get();
                for (size_t i = 0; i < result.size(); ++i) {
                    for (size_t j = 0; j < result[i].size(); ++j) {
                        if (j > 0) {
                            cout << "\t";
                        }
                        cout << result[i][j];
                    }
                    cout << endl;
                }
                cout << endl;
                futureQueue.pop();
            }
            sentence.clear();
        } else {
            auto split = splitStringByTabs(line);
            sentence.push_back(split[0]);
        }
    }
    while (!futureQueue.empty()) {
        futureQueue.front().wait();
        const auto result = futureQueue.front().get();
        for (size_t i = 0; i < result.size(); ++i) {
            for (size_t j = 0; j < result[i].size(); ++j) {
                if (j > 0) {
                    cout << "\t";
                }
                cout << result[i][j];
            }
            cout << endl;
        }
        cout << endl;
        futureQueue.pop();
    }

    return 0;
}


MorphemeTaggerClass::MorphemeTaggerClass(const MorphemeTaggerOptions &options) {
    this->options = options;
    assert(!options.dictionaryFilename.empty());
    dictionary = make_shared<Dictionary>(options.dictionaryFilename);
};

void MorphemeTaggerClass::train(const string &trainingFilename,
                                const string &modelFilename) {
    ifstream ifs(trainingFilename);
    vector<Observation> observationList;

    while (true) {
        vector<string> sentence;
        vector<vector<string>> correctResultList;
        readSentence(&ifs, &sentence, &correctResultList, true);
        if (sentence.empty()) {
            break;
        }
        auto dictResultListList = lookupSentence(sentence, *dictionary);
        auto commonAttributeSetList = convertSentenceToCommonAttributeSetList(sentence, dictResultListList, options);
        assert(sentence.size() == dictResultListList.size() &&
               sentence.size() == commonAttributeSetList.size());
        for (size_t i = 0; i < sentence.size(); ++i) {
            auto o = generateTrainingObservationList(*dictResultListList[i], commonAttributeSetList[i], correctResultList[i]);
            move(o.begin(), o.end(), back_inserter(observationList));
        }
    }
    ifs.close();

    MaxEntProcessor maxent;
    maxent.train(observationList, options.numThreads, 10000, false, 10.0, 0.00001);
    maxent.writeModel(modelFilename);
}

vector<vector<string>> MorphemeTaggerClass::tag(vector<string> sentence) const {
    vector<vector<string>> ret;
    if (sentence.empty()) {
        return ret;
    }
    auto dictResultListList = lookupSentence(sentence, *dictionary);
    auto commonAttributeSetList = convertSentenceToCommonAttributeSetList(sentence, dictResultListList, options);
    assert(sentence.size() == dictResultListList.size() &&
           sentence.size() == commonAttributeSetList.size());
    for (size_t i = 0; i < sentence.size(); ++i) {
        vector<string> result = { sentence[i] };
        if (dictResultListList[i]->size() != 0) {
            size_t j = inferCorrectResult(*dictResultListList[i], commonAttributeSetList[i], *maxEntProcessor);
            auto &inferredResult = (*dictResultListList[i])[j];
            result.insert(result.end(), inferredResult.begin(), inferredResult.end());
        }
        ret.push_back(move(result));
    }
    return ret;
}

void MorphemeTaggerClass::test(const string &testFilename) const {
    ifstream ifs(testFilename);

    size_t correctCount = 0;
    size_t allCount = 0;
    while (true) {
        vector<string> sentence;
        vector<vector<string>> correctResultList;
        readSentence(&ifs, &sentence, &correctResultList, true);
        if (sentence.empty()) {
            break;
        }
        auto inferredResultList = tag(sentence);
        assert(inferredResultList.size() == correctResultList.size());
        for (size_t i = 0; i < inferredResultList.size(); ++i) {
            if (inferredResultList[i].size() == correctResultList[i].size() + 1 &&
                equal(inferredResultList[i].begin() + 1, inferredResultList[i].end(), correctResultList[i].begin())) {
                ++correctCount;
            }
            ++allCount;
        }
    }
    ifs.close();
    printf("Accuracy: %d / %d (%1.4f)\n", correctCount, allCount, correctCount / (double)allCount);
}

void MorphemeTaggerClass::readModel(const string &modelFilename) {
    maxEntProcessor = make_shared<MaxEntProcessor>();
    maxEntProcessor->readModel(modelFilename);
}

}  // namespace MorphemeTagger

int main(int argc, char **argv) {
    return MorphemeTagger::mainProc(argc, argv);
}

