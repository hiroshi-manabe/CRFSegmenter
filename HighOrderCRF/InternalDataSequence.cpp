#include "InternalDataSequence.h"

#include "Pattern.h"
#include "PatternSetSequence.h"
#include "Feature.h"
#include "FeatureTemplate.h"
#include "LabelSequence.h"
#include "Trie.h"

#include <algorithm>
#include <iterator>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace HighOrderCRF {

using std::back_inserter;
using std::make_pair;
using std::make_shared;
using std::min;
using std::move;
using std::reverse_copy;
using std::shared_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

InternalDataSequence::InternalDataSequence(vector<label_t> labels, vector<unordered_set<label_t>> possibleLabelSetList, vector<vector<FeatureTemplate>> featureTemplateListList) {
    this->labels = move(labels);
    this->possibleLabelSetList = move(possibleLabelSetList);
    this->featureTemplateListList = move(featureTemplateListList);
}

size_t InternalDataSequence::length() const {
    return featureTemplateListList.size();
}

LabelSequence InternalDataSequence::getLabelSequence(size_t pos, size_t length) const {
    if (pos < length - 1) {
        return LabelSequence();
    }
    vector<label_t> labels;
    for (size_t i = 0; i < length; ++i) {
        labels.push_back(this->labels.at(pos - i));
    }
    return LabelSequence(move(labels));
}

const vector<label_t> &InternalDataSequence::getLabels() const {
    return labels;
}

void InternalDataSequence::accumulateFeatureData(unordered_map<FeatureTemplate, vector<uint32_t>> *featureTemplateToFeatureIndexListMap,
                                                 unordered_map<Feature, uint32_t> *featureToFeatureIndexMap,
                                                 vector<double> *featureCountList) const {
    for (size_t pos = 0; pos < labels.size(); ++pos) {
        for (auto &ft : featureTemplateListList[pos]) {
            if (pos < ft.getLabelLength() - 1) {
                continue;
            }
            Feature f(ft.getTag(), getLabelSequence(pos, ft.getLabelLength()));
            auto it = featureToFeatureIndexMap->find(f);
            if (it == featureToFeatureIndexMap->end()) {
                auto index = (uint32_t)featureToFeatureIndexMap->size();
                it = featureToFeatureIndexMap->insert(make_pair(f, index)).first;
                featureCountList->push_back(0);
                auto it2 = featureTemplateToFeatureIndexListMap->find(ft);
                if (it2 == featureTemplateToFeatureIndexListMap->end()) {
                    it2 = featureTemplateToFeatureIndexListMap->insert(make_pair(ft, vector<uint32_t>())).first;
                }
                it2->second.push_back(it->second);
            }
            ++(*featureCountList)[it->second];
        }
    }
}

struct PatternData {
    vector<feature_index_t> featureIndexList;
    pattern_index_t patternIndex;
};

template<typename L>
struct PatternGenerationData {
    vector<PatternData> *patternDataList;
    vector<Pattern> *patternList;
    Trie<L> *prevTrie;
    pattern_index_t currentIndex;
};

void generatePatternSetProc(label_t *labels, size_t size, int dataIndex, int parentDataIndex, void *data) {
    auto generationData = static_cast<PatternGenerationData<label_t> *>(data);
    pattern_index_t prevPatternIndex = 0;
    if (generationData->prevTrie && size > 0) {
        prevPatternIndex = (*generationData->patternDataList)[generationData->prevTrie->find(labels + 1, size - 1)].patternIndex;
    }
    PatternData &thisPatternData = (*generationData->patternDataList)[dataIndex];
    thisPatternData.patternIndex = generationData->currentIndex;
    ++generationData->currentIndex;
    PatternData &suffixPatternData = (*generationData->patternDataList)[parentDataIndex];
    pattern_index_t suffixPatternIndex = suffixPatternData.patternIndex;
    generationData->patternList->emplace_back(prevPatternIndex, suffixPatternIndex, size ? labels[0] : INVALID_LABEL, vector<feature_index_t>(thisPatternData.featureIndexList));
}

shared_ptr<PatternSetSequence> InternalDataSequence::generatePatternSetSequence(const unordered_map<FeatureTemplate, vector<uint32_t>> &featureTemplateToFeatureIndexListMap, const vector<uint32_t> &featureLabelSequenceIndexList, const vector<LabelSequence> &labelSequenceList, bool hasValidLabels) const {
    vector<Trie<label_t>> trieList(this->length());
    vector<PatternData> patternDataList;
    auto emptyLabelSequence = LabelSequence::createEmptyLabelSequence();
    
    for (size_t pos = 0; pos < this->length(); ++pos) {
        const auto &curFeatureTemplateList = featureTemplateListList[pos];
        auto &curTrie = trieList[pos];
        int dataIndex = curTrie.findOrInsert(emptyLabelSequence.getLabelData(), emptyLabelSequence.getLength(), patternDataList.size());
        if (dataIndex == patternDataList.size()) {
            patternDataList.emplace_back();
        }

        for (const auto &featureTemplate : curFeatureTemplateList) {
            if (featureTemplate.getLabelLength() > pos + 1) {
                continue;
            }
            auto featureIndexList = featureTemplateToFeatureIndexListMap.find(featureTemplate);
            if (featureIndexList == featureTemplateToFeatureIndexListMap.end()) {
                continue;
            }
            for (auto &featureIndex : featureIndexList->second) {
                auto seq = labelSequenceList[featureLabelSequenceIndexList[featureIndex]];

                bool labelsOK = true;
                for (size_t i = 0; i < seq.getLength(); ++i) {
                    if (!possibleLabelSetList[pos - i].empty() && possibleLabelSetList[pos - i].find(seq.getLabelAt(i)) == possibleLabelSetList[pos - i].end()) {
                        labelsOK = false;
                        break;
                    }
                }
                if (!labelsOK) {
                    continue;
                }
                int dataIndex = curTrie.findOrInsert(seq.getLabelData(), seq.getLength(), patternDataList.size());
                if (dataIndex == patternDataList.size()) {
                    patternDataList.emplace_back();
                }

                patternDataList[dataIndex].featureIndexList.push_back(featureIndex);

                if (pos > 0) {
                    size_t labelLength = seq.getLength();
                    for (size_t i = 1; i <= min(labelLength - 1, pos); ++i) {
                        auto &prevTrie = trieList[pos - i];
                        int prevDataIndex = prevTrie.findOrInsert(seq.getLabelData() + i, seq.getLength() - i, patternDataList.size());
                        if (prevDataIndex == patternDataList.size()) {
                            patternDataList.emplace_back();
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }

    auto patternListList = vector<vector<Pattern>>();
    auto longestMatchIndexList = vector<pattern_index_t>();
    vector<label_t> reversedLabels;
    reversedLabels.reserve(labels.size());

    reverse_copy(labels.begin(), labels.end(), back_inserter(reversedLabels));
    
    for (size_t pos = 0; pos < this->length(); ++pos) {
        Trie<label_t> &curTrie = trieList[pos];
        if (curTrie.isEmpty()) {
            label_t l = 0;
            if (!possibleLabelSetList[pos].empty()) {
                l = *(possibleLabelSetList[pos].begin());
            }
            int dataIndex = curTrie.findOrInsert(&l, 1, patternDataList.size());
            if (dataIndex == patternDataList.size()) {
                patternDataList.emplace_back();
            }
        }

        vector<Pattern> patternList;
        PatternGenerationData<label_t> d;
        d.patternDataList = &patternDataList;
        d.patternList = &patternList;
        d.prevTrie = pos ? &trieList[pos - 1] : 0;
        d.currentIndex = 0;
        
        curTrie.visitValidNodes(generatePatternSetProc, (void *)&d);
        patternListList.push_back(move(patternList));

        pattern_index_t longestMatchIndex = 0;
        if (hasValidLabels) {
            longestMatchIndex = patternDataList[curTrie.findLongestMatch(reversedLabels.data() + this->length() - pos - 1, pos + 1)].patternIndex;
        }
        longestMatchIndexList.push_back(longestMatchIndex);
    }
    return make_shared<PatternSetSequence>(move(patternListList), move(longestMatchIndexList));
}

}  // namespace HighOrderCRF
