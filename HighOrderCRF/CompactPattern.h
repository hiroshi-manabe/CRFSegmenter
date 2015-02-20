#ifndef HOCRF_COMPACT_PATTERN_H_
#define HOCRF_COMPACT_PATTERN_H_

#include "types.h"

#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::shared_ptr;
using std::vector;

class Feature;

struct CompactPattern
{
    CompactPattern() {};
    CompactPattern(pattern_index_t prevPatternIndex,
                   pattern_index_t longestSuffixIndex,
                   label_t lastLabel,
                   shared_ptr<vector<feature_index_t>> featureIndexList) :
    prevPatternIndex(prevPatternIndex), longestSuffixIndex(longestSuffixIndex), lastLabel(lastLabel), featureIndexList(featureIndexList) {};
    shared_ptr<vector<feature_index_t>> getFeatureIndexList() const { return featureIndexList; }
    label_t getLastLabel() const { return lastLabel; }
    pattern_index_t getLongestSuffixIndex() const { return longestSuffixIndex; }
    pattern_index_t getPrevPatternIndex() const { return prevPatternIndex; }

private:
    pattern_index_t prevPatternIndex;
    pattern_index_t longestSuffixIndex;
    label_t lastLabel;
    shared_ptr<vector<feature_index_t>> featureIndexList;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_COMPACT_PATTERN_H
