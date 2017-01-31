#include "MorphemeDisambiguatorClass.h"

#include "../Dictionary/DictionaryClass.h"
#include "../MaxEnt/MaxEntProcessor.h"
#include "../Utility/StringUtil.h"
#include "MorphemeDisambiguatorOptions.h"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace MorphemeDisambiguator {

using Dictionary::DictionaryClass;
using MaxEnt::MaxEntProcessor;
using MaxEnt::Observation;

using std::back_inserter;
using std::cerr;
using std::endl;
using std::equal;
using std::getline;
using std::ifstream;
using std::istream;
using std::make_shared;
using std::move;
using std::set;
using std::showpos;
using std::string;
using std::stringstream;
using std::unordered_set;
using std::vector;

vector<vector<vector<string>>> lookupSentence(const vector<string> &sentence, const DictionaryClass &dictionary) {
    vector<vector<vector<string>>> ret;
    for (const auto &str : sentence) {
        auto result = dictionary.lookup(str);
        vector<vector<string>> ll;
        ll.reserve(result.size());
        for (const auto &entry : result) {
            vector<string> l;
            l.reserve(entry.size());
            for (const auto &element : entry) {
                l.emplace_back(*element);
            }
            ll.emplace_back(move(l));
        }
        ret.emplace_back(move(ll));
    }
    return ret;
}

vector<unordered_set<string>> convertSentenceToCommonAttributeSetList(const vector<string> &sentence, const vector<vector<vector<string>>> &dictResultListList, const MorphemeDisambiguatorOptions &opt) {
    assert(sentence.size() == dictResultListList.size());
    vector<vector<string>> wordAndLabelList;
    
    for (const auto &wordAndLabelStr : sentence) {
        auto wordAndLabel = Utility::rsplit2(wordAndLabelStr, '/');
        wordAndLabelList.emplace_back(move(wordAndLabel));
    }
    
    vector<unordered_set<string>> ret(sentence.size());
    for (size_t i = 0; i < sentence.size(); ++i) {
        unordered_set<string> commonAttributeSet;
        if (dictResultListList[i].size() < 2) {
            continue;
        }
        
        for (int j = -(int)opt.columnMaxWindow; j <= (int)opt.columnMaxWindow; ++j) {
            int pos = i + j;
            if (j == 0 || pos < 0 || pos >= (int)sentence.size()) {
                continue;
            }
            if (dictResultListList[pos].empty()) {
                continue;
            }
            stringstream posPrefix;
            posPrefix << "P" << showpos << j << "-";
            for (const auto &dictResult : dictResultListList[pos]) {
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
        vector<string> elems = Utility::splitString(line);
        if (elems.size() < (size_t)(hasCorrectResults ? 2 : 1)) {
            cerr << "Not properly tagged: " << line << endl;
        }
        sentence->emplace_back(elems[0]);
        correctResultList->emplace_back(elems.begin() + 1, elems.end());
    }
}

MorphemeDisambiguatorClass::MorphemeDisambiguatorClass(const MorphemeDisambiguatorOptions &options) {
    this->options = options;
    assert(!options.dictionaries.empty());
    dictionary = make_shared<DictionaryClass>(options.dictionaries);
};

void MorphemeDisambiguatorClass::train(const string &trainingFilename,
                                       size_t concurrency,
                                       size_t maxIter,
                                       double regularizationCoefficientL1,
                                       double regularizationCoefficientL2,
                                       double epsilonForConvergence,
                                       const std::string &modelFilename) {
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
            auto o = generateTrainingObservationList(dictResultListList[i], commonAttributeSetList[i], correctResultList[i]);
            move(o.begin(), o.end(), back_inserter(observationList));
        }
    }
    ifs.close();

    MaxEntProcessor maxent;
    maxent.train(observationList, concurrency, maxIter, regularizationCoefficientL1, regularizationCoefficientL2, epsilonForConvergence);
    maxent.writeModel(modelFilename);
}

vector<vector<string>> MorphemeDisambiguatorClass::tag(vector<string> sentence) const {
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
        if (dictResultListList[i].size() != 0) {
            size_t j = inferCorrectResult(dictResultListList[i], commonAttributeSetList[i], *maxEntProcessor);
            auto &inferredResult = (dictResultListList[i])[j];
            result.insert(result.end(), inferredResult.begin(), inferredResult.end());
        }
        ret.emplace_back(move(result));
    }
    return ret;
}

void MorphemeDisambiguatorClass::test(const string &testFilename) const {
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

void MorphemeDisambiguatorClass::readModel(const string &modelFilename) {
    maxEntProcessor = make_shared<MaxEntProcessor>();
    maxEntProcessor->readModel(modelFilename);
}

}  // namespace MorphemeDisambiguator

