#ifndef HOCRF_HIGH_ORDER_CRF_PATTERN_SET_SEQUENCE_H_
#define HOCRF_HIGH_ORDER_CRF_PATTERN_SET_SEQUENCE_H_

#include <atomic>
#include <unordered_map>
#include <vector>

#include "Pattern.h"
#include "types.h"

namespace HighOrderCRF {

class PatternSetSequence
{
public:
    PatternSetSequence(std::vector<std::vector<Pattern>> patternListList,
                       std::vector<pattern_index_t> longestMatchIndexList) :
    patternListList(move(patternListList)), longestMatchIndexList(longestMatchIndexList) {};
    void accumulateFeatureCounts(double *counts) const;
    double accumulateFeatureExpectations(const double *expWeights, std::vector<std::atomic_uint_least64_t> *expectations) const;
    std::vector<std::unordered_map<label_t, double>> calcLabelLikelihoods(const double *expWeights) const;
    std::vector<label_t> decode(const weight_t *weights) const;
    
private:
    double calcScores(const double *expWeights, std::vector<std::vector<double>> *scores) const;
    std::vector<std::vector<Pattern>> patternListList;
    std::vector<pattern_index_t> longestMatchIndexList;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_HIGH_ORDER_CRF_PATTERN_SET_SEQUENCE_H
