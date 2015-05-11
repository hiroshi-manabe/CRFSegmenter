#ifndef HOCRF_MAX_ENT_MAX_ENT_PROCESSOR_H_
#define HOCRF_MAX_ENT_MAX_ENT_PROCESSOR_H_

#include "../Optimizer/OptimizerClass.h"
#include "../task/task_queue.hpp"
#include "CompiledData.h"
#include "MaxEntData.h"
#include "Observation.h"

#include <cmath>
#include <cstdio>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace MaxEnt {

using std::future;
using std::make_shared;
using std::move;
using std::pair;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

class MaxEntData;

double maxEntUpdateProc(void *updateData, const double *x, double *g, size_t concurrency) {
    
    auto compiledDataList = static_cast<shared_ptr<vector<shared_ptr<CompiledData>>> *>(updateData);
    hwm::task_queue tq(concurrency);
    vector<future<double>> futureList;

    for (auto &data : **compiledDataList) {
        future<double> f = tq.enqueue([](shared_ptr<CompiledData> pat, const double* expWeightArray, double* expectationArray) -> double {
                return pat->accumulateFeatureExpectations(expWeightArray, expectationArray);
            },
            data,
            x,
            g);
        futureList.push_back(move(f));
    }
    tq.wait();

    double logLikelihood = 0.0;
    for (auto &f : futureList) {
        logLikelihood += f.get();
    }
    return logLikelihood;
}

class MaxEntProcessor
{
public:
    MaxEntProcessor() : modelData(new MaxEntData) {}
    void train(const vector<Observation> &observationList,
               size_t concurrency,
               size_t maxIters,
               bool useL1Regularization,
               double regularizationCoefficient,
               double epsilonForConvergence) {

        auto compiledDataList = make_shared<vector<shared_ptr<CompiledData>>>();
        auto labelToIndexMap = make_shared<unordered_map<string, size_t>>();
        auto attrToIndexMap = make_shared<unordered_map<string, size_t>>();
        auto indexPairToFeatureIndexMap = make_shared<unordered_map<pair<size_t, size_t>, size_t>>();
        compiledDataList->reserve(observationList.size());
        
        for (auto &obs : observationList) {
            compiledDataList->push_back(obs.compile(labelToIndexMap, attrToIndexMap, indexPairToFeatureIndexMap, true));
        }
        auto featureCountList = make_shared<vector<double>>(indexPairToFeatureIndexMap->size());
        for (auto &data : (*compiledDataList)) {
            data->accumulateFeatureCounts(featureCountList->data());
        }
        
        auto optimizer = make_shared<Optimizer::OptimizerClass>(maxEntUpdateProc, static_cast<void *>(&compiledDataList), featureCountList, concurrency, 0, false, regularizationCoefficient, epsilonForConvergence);
        auto initialWeightList = make_shared<vector<double>>(featureCountList->size());
        optimizer->optimize(initialWeightList->data());
        auto bestWeightList = optimizer->getBestWeightList();
        
        modelData = make_shared<MaxEntData>(labelToIndexMap, attrToIndexMap, indexPairToFeatureIndexMap, bestWeightList);
    }

    string inferLabel(const Observation &obs) const {
        return obs.compile(modelData->getLabelToIndexMap(), modelData->getAttrToIndexMap(), modelData->getIndexPairToFeatureIndexMap(), false)->inferLabel(modelData->getBestWeightList()->data());
    }

    void writeModel(const string &filename) {
        modelData->write(filename);
    }

    void readModel(const string &filename) {
        modelData->read(filename);
    }        
    
    shared_ptr<MaxEntData> modelData;
    shared_ptr<vector<double>> expWeightList;
    shared_ptr<vector<string>> labelStringList;
};

} // namespace MaxEnt

#endif // HOCRF_MAX_ENT_MAX_ENT_PROCESSOR_H_
