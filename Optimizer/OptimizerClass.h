#ifndef HOCRF_OPTIMIZER_OPTIMIZER_CLASS_H
#define HOCRF_OPTIMIZER_OPTIMIZER_CLASS_H

#include <memory>
#include <vector>

namespace Optimizer {

using std::make_shared;
using std::shared_ptr;
using std::vector;

class OptimizerClass
{
public:
    OptimizerClass(double (*updateProc)(void *, const double *, double *, size_t), void *updateData, shared_ptr<vector<double>> featureCountList, size_t concurrency, size_t maxIters, bool useL1Optimization, double regularizationCoefficient, double epsilonForConvergence);
    double evaluate(const double *x, double *g);
    void optimize(const double *featureWeights);
    int progress(const double *x, const double *g, const double fx, const double xnorm, const double gnorm, const double step, int n, int k, int ls);
    shared_ptr<vector<double>> getBestWeightList();

private:
    double (*updateProc)(void *, const double *, double *, size_t);
    void *updateData;
    shared_ptr<vector<double>> featureCountList;
    shared_ptr<vector<double>> buffer;
    shared_ptr<vector<double>> bestWeightList;
    size_t concurrency;
    size_t maxIters;
    bool useL1Optimization;
    double regularizationCoefficient;
    double epsilonForConvergence;
};

}  // namespace Optimizer
#endif  // HOCRF_OPTIMIZER_OPTIMIZER_CLASS_H
