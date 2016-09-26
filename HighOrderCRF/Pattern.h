#ifndef HOCRF_HIGH_ORDER_CRF_PATTERN_H_
#define HOCRF_HIGH_ORDER_CRF_PATTERN_H_

#include "types.h"

#include "Feature.h"

#include <memory>
#include <vector>

namespace HighOrderCRF {

struct Pattern
{
    Pattern() {};
    Pattern(pattern_index_t prevPatternIndex,
            pattern_index_t longestSuffixIndex,
            label_t lastLabel,
            std::vector<feature_index_t> featureIndexList) :
    prevPatternIndex(prevPatternIndex), longestSuffixIndex(longestSuffixIndex), lastLabel(lastLabel) {
        this->featureIndexList = move(featureIndexList);
    }
    const std::vector<feature_index_t> &getFeatureIndexList() const { return featureIndexList; }
    label_t getLastLabel() const { return lastLabel; }
    pattern_index_t getLongestSuffixIndex() const { return longestSuffixIndex; }
    pattern_index_t getPrevPatternIndex() const { return prevPatternIndex; }

private:
    pattern_index_t prevPatternIndex;
    pattern_index_t longestSuffixIndex;
    label_t lastLabel;
    std::vector<feature_index_t> featureIndexList;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_HIGH_ORDER_CRF_PATTERN_H
