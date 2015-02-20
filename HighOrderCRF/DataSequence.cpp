#include "DataSequence.h"

#include "CompactPatternSetSequence.h"
#include "Feature.h"
#include "FeatureTemplate.h"
#include "LabelSequence.h"
#include "Pattern.h"
#include "PatternSetSequence.h"

#include <algorithm>
#include <map>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace HighOrderCRF {

using std::make_shared;
using std::map;
using std::min;
using std::pair;
using std::shared_ptr;
using std::unordered_map;
using std::vector;

DataSequence::DataSequence(const shared_ptr<vector<shared_ptr<vector<shared_ptr<FeatureTemplate>>>>> featureTemplateListList,
    const shared_ptr<vector<label_t>> labels,
    bool hasValidLabels) {
    this->labels = labels;
    this->featureTemplateListList = featureTemplateListList;
    this->hasValidLabels = hasValidLabels;
}

size_t DataSequence::length() const {
    return featureTemplateListList->size();
}

shared_ptr<LabelSequence> DataSequence::getLabelSequence(size_t pos, size_t length) const {
    if (!hasValidLabels) {
        return LabelSequence::createEmptyLabelSequence();
    }
    if (pos < length - 1) {
        return LabelSequence::createEmptyLabelSequence();
    }
    auto labels = make_shared<vector<label_t>>();
    for (size_t i = 0; i < length; ++i) {
        labels->push_back(this->labels->at(pos - i));
    }
    return make_shared<LabelSequence>(labels);
}

void DataSequence::accumulateFeatureCountsToMap(shared_ptr<unordered_map<shared_ptr<Feature>, size_t>> featureCountMap) const {
    if (!hasValidLabels) {
        return;
    }
    for (size_t pos = 0; pos < labels->size(); ++pos) {
        for (auto &featureTemplate : *featureTemplateListList->at(pos)) {
            if (pos < featureTemplate->getLabelLength() - 1) {
                continue;
            }
            auto f = make_shared<Feature>(featureTemplate->getObservation(), getLabelSequence(pos, featureTemplate->getLabelLength()));
            auto it = featureCountMap->find(f);
            if (it == featureCountMap->end()) {
                featureCountMap->insert(pair<shared_ptr<Feature>, int32_t>(f, 1));
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

shared_ptr<CompactPatternSetSequence> DataSequence::generateCompactPatternSetSequence(const shared_ptr<unordered_map<shared_ptr<FeatureTemplate>, shared_ptr<vector<shared_ptr<Feature>>>>> featureTemplateToFeatureListMap) const {
    size_t maxLabelLength = 0;
    auto mapList = make_shared<vector<shared_ptr<map<shared_ptr<LabelSequence>, shared_ptr<Pattern>>>>>();
    auto emptyLabelSequence = LabelSequence::createEmptyLabelSequence();

    for (size_t pos = 0; pos < this->length(); ++pos) {
        auto &curFeatureTemplateList = featureTemplateListList->at(pos);
        mapList->push_back(make_shared<map<shared_ptr<LabelSequence>, shared_ptr<Pattern>>>());
        auto &curMap = mapList->at(pos);
        auto emptyPattern = make_shared<Pattern>(INVALID_LABEL);
        curMap->insert(pair<shared_ptr<LabelSequence>, shared_ptr<Pattern>>(emptyLabelSequence, emptyPattern));

        for (auto &featureTemplate : *curFeatureTemplateList) {
            if (featureTemplate->getLabelLength() > pos + 1) {
                continue;
            }
            if (featureTemplate->getLabelLength() > maxLabelLength) {
                maxLabelLength = featureTemplate->getLabelLength();
            }
            auto featureList = featureTemplateToFeatureListMap->find(featureTemplate);
            if (featureList == featureTemplateToFeatureListMap->end()) {
                continue;
            }
            for (auto &feature : *featureList->second) {
                auto seq = feature->getLabelSequence();

#ifdef EMULATE_BOS_EOS
                if (seq->getLabelAt(seq->getLength() - 1) == 0 && !(pos == seq->getLength() - 1 || seq->getLength() == 1 && pos == this->length() - 1)) {
                    continue;
                }
                if (seq->getLastLabel() == 0 && !(pos == this->length() - 1 || seq->getLength() == 1 && pos == 0)) {
                    continue;
                }
                if ((pos == 0 || pos == this->length() - 1) && (seq->getLength() != 1 || seq->getLastLabel() != 0)) {
                    continue;
                }
#endif

                if (curMap->find(seq) == curMap->end()) {
                    curMap->insert(pair<shared_ptr<LabelSequence>, shared_ptr<Pattern>>(seq, make_shared<Pattern>(seq->getLastLabel())));
                }

                auto &pat = curMap->at(seq);
                pat->addFeature(feature);

                if (pos == 0) {
                    pat->setPrevPattern(Pattern::getDummyPattern());
                } else {
                    size_t labelLength = seq->getLength();
                    auto &tempMap = mapList->at(pos);
                    for (size_t i = 1; i <= labelLength; ++i) {
                        auto &prevMap = mapList->at(pos - i);
                        auto prefix = seq->createPrefix();
                        
                        bool prevMapContainsKey = prevMap->find(prefix) != prevMap->end();
                        if (!prevMapContainsKey) {
                            prevMap->insert(pair<shared_ptr<LabelSequence>, shared_ptr<Pattern>>(prefix, make_shared<Pattern>(prefix->getLastLabel())));
                        }
                        tempMap->at(seq)->setPrevPattern(prevMap->at(prefix));
                        if (prevMapContainsKey) {
                            break;
                        }
                        seq = prefix;
                        tempMap = prevMap;
                    }
                }
            }
        }
    }
    auto patternListList = make_shared<vector<shared_ptr<vector<shared_ptr<Pattern>>>>>();
    auto longestMatchPatternList = make_shared<vector<shared_ptr<Pattern>>>();
    for (size_t pos = 0; pos < length(); ++pos) {
        auto &curMap = mapList->at(pos);
        auto longestSuffixCandidateList = make_shared<vector<shared_ptr<Pattern>>>();
        auto &emptyPattern = curMap->at(emptyLabelSequence);
        for (size_t i = 0; i < maxLabelLength + 1; ++i) {
            longestSuffixCandidateList->push_back(emptyPattern);
        }

        auto prevLabelSequence = emptyLabelSequence;
        for (auto &entry : *curMap) {
            auto &curLabelSequence = entry.first;
            auto &curPattern = entry.second;
            if (curLabelSequence == emptyLabelSequence) {
                continue;
            }
            size_t diffPos = curLabelSequence->getDifferencePosition(prevLabelSequence);
            curPattern->setLongestSuffixPattern(longestSuffixCandidateList->at(diffPos));
            for (size_t i = diffPos + 1; i < curLabelSequence->getLength(); ++i) {
                longestSuffixCandidateList->at(i) = longestSuffixCandidateList->at(diffPos);
            }
            longestSuffixCandidateList->at(curLabelSequence->getLength()) = curPattern;
            prevLabelSequence = curLabelSequence;
        }

        auto patternList = make_shared<vector<shared_ptr<Pattern>>>();
        for (auto &entry : *mapList->at(pos)) {
            patternList->push_back(entry.second);
        }
        auto &longestMatchPattern = patternList->at(0);
        if (hasValidLabels) {
            auto& prevMap = mapList->at(pos);
            for (size_t length = min(maxLabelLength, pos + 1); length > 0; --length) {
                auto key = getLabelSequence(pos, length);
                if (prevMap->find(key) != prevMap->end()) {
                    longestMatchPattern = prevMap->at(key);
                    break;
                }
            }
        }
        patternListList->push_back(patternList);
        longestMatchPatternList->push_back(longestMatchPattern);
    }
    return PatternSetSequence(patternListList, longestMatchPatternList).generateCompactPatternSetSequence();
}

}  // namespace HighOrderCRF
