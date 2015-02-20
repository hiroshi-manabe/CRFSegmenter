#include "Optimizer.h"

#include "lbfgs.h"
#include "CompactPatternSetSequence.h"

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;
using std::vector;

double lbfgsEvaluate(void *instance,
                              const double *x,
                              double *g,
                              const int n,
                              const double step) {
    return ((Optimizer*)instance)->evaluate(x, g);
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
    return ((Optimizer*)instance)->progress(x, g, fx, xnorm, gnorm, step, n, k, ls);
}

Optimizer::Optimizer(shared_ptr<vector<shared_ptr<CompactPatternSetSequence>>> sequenceList, shared_ptr<vector<double>> featureCountList, size_t maxIters, bool useL1Optimization, double regularizationCoefficient, double epsilonForConvergence) {
    this->sequenceList = sequenceList;
    this->featureCountList = featureCountList;
    this->maxIters = maxIters;
    this->useL1Optimization = useL1Optimization;
    this->regularizationCoefficient = regularizationCoefficient;
    this->epsilonForConvergence = epsilonForConvergence;
}

void Optimizer::optimize(const double* featureWeights) {
    lbfgs_parameter_t lbfgsParam;
    lbfgs_parameter_init(&lbfgsParam);
    lbfgsParam.max_linesearch = 20;
    lbfgsParam.past = 10;

    cout << "L-BFGS optimization" << endl;
    size_t featureListSize = featureCountList->size();
    bestWeightList = make_shared<vector<double>>(featureListSize);
    buffer = make_shared<vector<double>>(featureListSize);
    
    if (maxIters != 0) {
        lbfgsParam.max_iterations = maxIters;
    }
    if (epsilonForConvergence != 0.0) {
        lbfgsParam.epsilon = epsilonForConvergence;
    }
    if (useL1Optimization) {
        lbfgsParam.orthantwise_c = 1.0 / regularizationCoefficient;
        lbfgsParam.linesearch = LBFGS_LINESEARCH_BACKTRACKING;
    } else {
        lbfgsParam.orthantwise_c = 0.0;
    }
    auto ret = lbfgs(featureListSize, buffer->data(), 0, lbfgsEvaluate, lbfgsProgress, this, &lbfgsParam);

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

double Optimizer::evaluate(const double *x, double *g) {
    size_t featureListSize = featureCountList->size();
    vector<double> expWeights(featureListSize);

    for (size_t i = 0; i < featureListSize; ++i) {
        // sets exponential weights
        expWeights[i] = exp(x[i]);
        g[i] = -(*featureCountList)[i];
    }

    double logLikelihood = 0.0;
    for (auto &sequence : *sequenceList) {
        logLikelihood += sequence->accumulateFeatureExpectations(expWeights.data(), g);
    }

    if (!useL1Optimization) {
        double sigma2inv = 1.0 / (regularizationCoefficient * regularizationCoefficient);
        for (size_t i = 0; i < featureListSize; ++i) {
            g[i] += x[i] * sigma2inv;
            logLikelihood -= x[i] * x[i] * 0.5 * sigma2inv;
        }
    }
    return -logLikelihood;
}

int Optimizer::progress(const double *x,
                        const double *g,
                        const double fx,
                        const double xnorm,
                        const double gnorm,
                        const double step,
                        int n,
                        int k,
                        int ls) {
    size_t activeFeatureCount = 0;
    for (size_t i = 0; i < featureCountList->size(); ++i) {
        (*bestWeightList)[i] = x[i];
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

shared_ptr<vector<double>> Optimizer::getBestWeightList() {
    return bestWeightList;
}

}  // namespace HighOrderCRF
