#ifndef HOCRF_OPTIMIZER_H
#define HOCRF_OPTIMIZER_H

#include "types.h"

#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::make_shared;
using std::shared_ptr;
using std::vector;

class CompactPatternSetSequence;

class Optimizer
{
public:
    Optimizer(shared_ptr<vector<shared_ptr<CompactPatternSetSequence>>> sequenceList, shared_ptr<vector<double>> featureCountList, size_t concurrency, size_t maxIters, bool useL1Optimization, double regularizationCoefficient, double epsilonForConvergence);
    double evaluate(const double *x, double *g);
    void optimize(const double *featureWeights);
    int progress(const double *x, const double *g, const double fx, const double xnorm, const double gnorm, const double step, int n, int k, int ls);
    shared_ptr<vector<double>> getBestWeightList();

private:
    shared_ptr<vector<shared_ptr<CompactPatternSetSequence>>> sequenceList;
    shared_ptr<vector<double>> featureCountList;
    shared_ptr<vector<double>> buffer;
    shared_ptr<vector<double>> bestWeightList;
    size_t concurrency;
    size_t maxIters;
    bool useL1Optimization;
    double regularizationCoefficient;
    double epsilonForConvergence;
};

}  // namespace HighOrderCRF
#endif  // HOCRF_OPTIMIZER_H
