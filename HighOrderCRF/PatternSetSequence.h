#ifndef HOCRF_HIGH_ORDER_CRF_PATTERN_SET_SEQUENCE_H_
#define HOCRF_HIGH_ORDER_CRF_PATTERN_SET_SEQUENCE_H_

#include "types.h"

#include <memory>
#include <unordered_map>
#include <vector>

namespace HighOrderCRF {

using std::shared_ptr;
using std::unordered_map;
using std::vector;

struct Pattern;

class PatternSetSequence
{
public:
    PatternSetSequence(shared_ptr<vector<vector<Pattern>>> &patternListList,
                       shared_ptr<vector<pattern_index_t>> longestMatchIndexList) :
    patternListList(patternListList), longestMatchIndexList(longestMatchIndexList) {};
    void accumulateFeatureCounts(double *counts) const;
    double accumulateFeatureExpectations(const double *expWeights, double *expectations) const;
    vector<unordered_map<label_t, double>> calcLabelLikelihoods(const double *expWeights) const;
    vector<label_t> decode(const weight_t *expWeights) const;
    double calcLogLikelihood() const;
    
private:
    double calcScores(const double *expWeights, vector<vector<double>> *scores) const;
    shared_ptr<vector<vector<Pattern>>> patternListList;
    shared_ptr<vector<pattern_index_t>> longestMatchIndexList;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_HIGH_ORDER_CRF_PATTERN_SET_SEQUENCE_H
