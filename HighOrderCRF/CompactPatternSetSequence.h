#ifndef HOCRF_HIGH_ORDER_CRF_COMPACT_PATTERN_SET_SEQUENCE_H_
#define HOCRF_HIGH_ORDER_CRF_COMPACT_PATTERN_SET_SEQUENCE_H_

#include "types.h"

#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::make_shared;
using std::shared_ptr;
using std::vector;

struct CompactPattern;

class CompactPatternSetSequence
{
public:
    CompactPatternSetSequence(shared_ptr<vector<vector<CompactPattern>>> &compactPatternListList,
        shared_ptr<vector<pattern_index_t>> longestMatchIndexList) :
        compactPatternListList(compactPatternListList), longestMatchIndexList(longestMatchIndexList) {};
    void accumulateFeatureCounts(double *counts) const;
    double accumulateFeatureExpectations(double *expWeights, double *expectations) const;
    shared_ptr<vector<label_t>> decode(double *expWeights) const;
    double calcLogLikelihood() const;
    
private:
    shared_ptr<vector<vector<CompactPattern>>> compactPatternListList;
    shared_ptr<vector<pattern_index_t>> longestMatchIndexList;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_HIGH_ORDER_CRF_COMPACT_PATTERN_SET_SEQUENCE_H
