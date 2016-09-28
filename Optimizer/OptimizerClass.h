#ifndef HOCRF_OPTIMIZER_OPTIMIZER_CLASS_H
#define HOCRF_OPTIMIZER_OPTIMIZER_CLASS_H

#include <memory>
#include <vector>

namespace Optimizer {

class OptimizerClass
{
public:
    OptimizerClass(double (*updateProc)(void *, const double *, double *, size_t), void *updateData, std::vector<double> featureCountList, size_t concurrency, size_t maxIters, double  regularizationCoefficientL1, double regularizationCoefficientL2, double epsilonForConvergence);
    double evaluate(const double *x, double *g);
    void optimize(const double *featureWeights);
    int progress(const double *x, const double *g, const double fx, const double xnorm, const double gnorm, const double step, int n, int k, int ls);
    const std::vector<double> &getBestWeightList();

private:
    double (*updateProc)(void *, const double *, double *, size_t);
    void *updateData;
    std::vector<double> featureCountList;
    std::vector<double> buffer;
    std::vector<double> bestWeightList;
    size_t concurrency;
    size_t maxIter;
    double regularizationCoefficientL1;
    double regularizationCoefficientL2;
    double epsilonForConvergence;
};

}  // namespace Optimizer
#endif  // HOCRF_OPTIMIZER_OPTIMIZER_CLASS_H
