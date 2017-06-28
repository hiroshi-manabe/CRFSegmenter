#include "OptimizerClass.h"

#include "../liblbfgs/lbfgs.h"
#include "../task/task_queue.hpp"

#include <cmath>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

namespace Optimizer {

using std::cout;
using std::endl;
using std::move;
using std::vector;

double lbfgsEvaluate(void *instance,
                     const double *x,
                     double *g,
                     const int n,
                     const double step) {
    return ((OptimizerClass*)instance)->evaluate(x, g, n);
}

int lbfgsProgress(void *instance,
                   const double *x,
                   const double *g,
                   const double fx,
                   const double xnorm,
                   const double gnorm,
                   const double step,
                   int n,
                   int k,
                   int ls) {
    return ((OptimizerClass*)instance)->progress(x, g, fx, xnorm, gnorm, step, n, k, ls);
}

OptimizerClass::OptimizerClass(double (*updateProc)(void *, const double *, double *, int, size_t), void *updateData, vector<double> featureCountList,
    size_t concurrency, size_t maxIter, double regularizationCoefficientL1, double regularizationCoefficientL2, double epsilonForConvergence) {
    this->updateProc = updateProc;
    this->updateData = updateData;
    this->featureCountList = move(featureCountList);
    this->concurrency = concurrency;
    this->maxIter = maxIter;
    this->regularizationCoefficientL1 = regularizationCoefficientL1;
    this->regularizationCoefficientL2 = regularizationCoefficientL2;
    this->epsilonForConvergence = epsilonForConvergence;
}

void OptimizerClass::optimize(const double* featureWeights) {
    lbfgs_parameter_t lbfgsParam;
    lbfgs_parameter_init(&lbfgsParam);
    lbfgsParam.max_linesearch = 20;
    lbfgsParam.past = 10;

    cout << "L-BFGS optimization" << endl;
    size_t featureListSize = featureCountList.size();
    bestWeightList.resize(featureListSize);
    buffer.resize(featureListSize);
    
    if (maxIter != 0) {
        lbfgsParam.max_iterations = maxIter;
    }
    if (epsilonForConvergence != 0.0) {
        lbfgsParam.epsilon = epsilonForConvergence;
    }
    if (regularizationCoefficientL1 > 0.0) {
        lbfgsParam.orthantwise_c = regularizationCoefficientL1;
        lbfgsParam.linesearch = LBFGS_LINESEARCH_BACKTRACKING;
    } else {
        lbfgsParam.orthantwise_c = 0.0;
    }
    auto ret = lbfgs(featureListSize, buffer.data(), 0, lbfgsEvaluate, lbfgsProgress, this, &lbfgsParam);

    if (ret == LBFGS_CONVERGENCE) {
        cout << "L-BFGS resulted in convergence." << endl;
    } else if (ret == LBFGS_STOP) {
        cout << "L-BFGS terminated with the stopping criteria" << endl;
    } else if (ret == LBFGSERR_MAXIMUMITERATION) {
        cout << "L-BFGS terminated with the maximum number of iterations" << endl;
    } else {
        cout << "L-BFGS terminated with error code " << ret << endl;
    }
};

double OptimizerClass::evaluate(const double *x, double *g, int n) {
    size_t featureListSize = featureCountList.size();
    vector<double> expWeights(featureListSize);

    for (size_t i = 0; i < featureListSize; ++i) {
        // sets exponential weights
        expWeights[i] = exp(x[i]);
        g[i] = -featureCountList[i];
    }

    double logLikelihood = updateProc(updateData, expWeights.data(), g, n, concurrency);

    if (regularizationCoefficientL2 > 0.0) {
        for (size_t i = 0; i < featureListSize; ++i) {
            g[i] += x[i] * 2 * regularizationCoefficientL2;
            logLikelihood -= x[i] * x[i] * regularizationCoefficientL2;
        }
    }

    return -logLikelihood;
}

int OptimizerClass::progress(const double *x,
                        const double *g,
                        const double fx,
                        const double xnorm,
                        const double gnorm,
                        const double step,
                        int n,
                        int k,
                        int ls) {
    size_t activeFeatureCount = 0;
    for (size_t i = 0; i < featureCountList.size(); ++i) {
        bestWeightList[i] = x[i];
        if (x[i] != 0.0) {
            ++activeFeatureCount;
        }
    }
    cout << "***** Iteration #" << k << "*****" << endl;
    cout << "Log-likelihood: " << -fx << endl;
    cout << "Feature norm: " << xnorm << endl;
    cout << "Error norm: " << gnorm << endl;
    cout << "Active features :" << activeFeatureCount << endl;
    cout << "Line search trials: " << ls << endl;
    cout << "Line search step: " << step << endl << endl;
    return 0;
}

const vector<double> &OptimizerClass::getBestWeightList() {
    return bestWeightList;
}

}  // namespace Optimizer
