#include "DataSequence.h"

#include "Pattern.h"
#include "PatternSetSequence.h"
#include "Feature.h"
#include "FeatureTemplate.h"
#include "LabelSequence.h"
#include "Trie.h"

#include <algorithm>
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
using std::pair;
using std::reverse_copy;
using std::shared_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

DataSequence::DataSequence(shared_ptr<vector<vector<shared_ptr<FeatureTemplate>>>> featureTemplateListList,
                           shared_ptr<vector<label_t>> labels,
                           shared_ptr<vector<unordered_set<label_t>>> possibleLabelTypeSetList,
                           bool hasValidLabels) {
    this->labels = labels;
    this->featureTemplateListList = featureTemplateListList;
    this->possibleLabelTypeSetList = possibleLabelTypeSetList;
    this->hasValidLabels = hasValidLabels;
}

size_t DataSequence::length() const {
    return featureTemplateListList->size();
}

LabelSequence DataSequence::getLabelSequence(size_t pos, size_t length) const {
    if (!hasValidLabels) {
        return LabelSequence::createEmptyLabelSequence();
    }
    if (pos < length - 1) {
        return LabelSequence::createEmptyLabelSequence();
    }
    vector<label_t> labels;
    for (size_t i = 0; i < length; ++i) {
        labels.push_back(this->labels->at(pos - i));
    }
    return LabelSequence(labels);
}

void DataSequence::accumulateFeatureCountsToMap(shared_ptr<unordered_map<shared_ptr<Feature>, size_t>> featureCountMap) const {
    if (!hasValidLabels) {
        return;
    }
    for (size_t pos = 0; pos < labels->size(); ++pos) {
        for (auto &featureTemplate : (*featureTemplateListList)[pos]) {
            if (pos < featureTemplate->getLabelLength() - 1) {
                continue;
            }
            auto f = make_shared<Feature>(featureTemplate->getObservation(), getLabelSequence(pos, featureTemplate->getLabelLength()));
            auto it = featureCountMap->find(f);
            if (it == featureCountMap->end()) {
                featureCountMap->insert(make_pair(f, 1));
            } else {
                it->second += 1;
            }
#ifdef EMULATE_BOS_EOS
            if (pos == 0 || pos == labels->size() - 1) {
                featureCountMap->find(f)->second -= 1;
            }
#endif
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
    generationData->patternList->emplace_back(prevPatternIndex, suffixPatternIndex, size ? labels[0] : INVALID_LABEL, make_shared<vector<feature_index_t>>(move(thisPatternData.featureIndexList)));
}

shared_ptr<PatternSetSequence> DataSequence::generatePatternSetSequence(const shared_ptr<unordered_map<shared_ptr<FeatureTemplate>, shared_ptr<vector<const Feature *>>>> featureTemplateToFeatureListMap, const Feature *firstFeature) const {
    
    vector<Trie<label_t>> trieList(this->length());
    vector<PatternData> patternDataList;
    auto emptyLabelSequence = LabelSequence::createEmptyLabelSequence();
    
    for (size_t pos = 0; pos < this->length(); ++pos) {
        const auto &curFeatureTemplateList = (*featureTemplateListList)[pos];
        auto &curTrie = trieList[pos];
        int dataIndex = curTrie.findOrInsert(emptyLabelSequence.getLabelData(), emptyLabelSequence.getLength(), patternDataList.size());
        if (dataIndex == patternDataList.size()) {
            patternDataList.emplace_back();
        }

        for (const auto &featureTemplate : curFeatureTemplateList) {
            if (featureTemplate->getLabelLength() > pos + 1) {
                continue;
            }
            auto featureList = featureTemplateToFeatureListMap->find(featureTemplate);
            if (featureList == featureTemplateToFeatureListMap->end()) {
                continue;
            }
            for (auto &feature : *featureList->second) {
                auto seq = feature->getLabelSequence();

                bool labelsOK = true;
                for (size_t i = 0; i < seq.getLength(); ++i) {
                    if (!(*possibleLabelTypeSetList)[pos - i].empty() && (*possibleLabelTypeSetList)[pos - i].find(seq.getLabelAt(i)) == (*possibleLabelTypeSetList)[pos - i].end()) {
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

                patternDataList[dataIndex].featureIndexList.push_back(feature - firstFeature);

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

    auto patternListList = make_shared<vector<vector<Pattern>>>();
    auto longestMatchIndexList = make_shared<vector<pattern_index_t>>();
    vector<label_t> reversedLabels;
    reverse_copy(labels->begin(), labels->end(), back_inserter(reversedLabels));
    
    for (size_t pos = 0; pos < this->length(); ++pos) {
        Trie<label_t> &curTrie = trieList[pos];

        vector<Pattern> patternList;
        PatternGenerationData<label_t> d;
        d.patternDataList = &patternDataList;
        d.patternList = &patternList;
        d.prevTrie = pos ? &trieList[pos - 1] : 0;
        d.currentIndex = 0;
        
        curTrie.visitValidNodes(generatePatternSetProc, (void *)&d);
        patternListList->push_back(move(patternList));

        pattern_index_t longestMatchIndex = 0;
        if (hasValidLabels) {
            longestMatchIndex = patternDataList[curTrie.findLongestMatch(reversedLabels.data() + this->length() - pos - 1, pos + 1)].patternIndex;
        }
        longestMatchIndexList->push_back(longestMatchIndex);
    }
    return make_shared<PatternSetSequence>(patternListList, longestMatchIndexList);
}

}  // namespace HighOrderCRF
