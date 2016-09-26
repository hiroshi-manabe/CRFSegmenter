#ifndef HOCRF_MAX_ENT_MAX_ENT_PROCESSOR_H_
#define HOCRF_MAX_ENT_MAX_ENT_PROCESSOR_H_

#include "../Optimizer/OptimizerClass.h"
#include "../task/task_queue.hpp"
#include "CompiledData.h"
#include "MaxEntData.h"
#include "Observation.h"

#include <cmath>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace MaxEnt {

class MaxEntData;

double maxEntUpdateProc(void *updateData, const double *x, double *g, size_t concurrency) {
    
    auto compiledDataList = static_cast<std::shared_ptr<std::vector<std::shared_ptr<CompiledData>>> *>(updateData);
    hwm::task_queue tq(concurrency);
    std::vector<std::future<double>> futureList;

    for (auto &data : **compiledDataList) {
        std::future<double> f = tq.enqueue([](std::shared_ptr<CompiledData> pat, const double* expWeightArray, double* expectationArray) -> double {
                return pat->accumulateFeatureExpectations(expWeightArray, expectationArray);
            },
            data,
            x,
            g);
        futureList.push_back(std::move(f));
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
    void train(const std::vector<Observation> &observationList,
               size_t concurrency,
               size_t maxIters,
               bool useL1Regularization,
               double regularizationCoefficient,
               double epsilonForConvergence) {

        auto compiledDataList = std::make_shared<std::vector<std::shared_ptr<CompiledData>>>();
        std::unordered_map<std::string, uint32_t> labelToIndexMap;
        std::unordered_map<std::string, uint32_t> attrToIndexMap;
        std::unordered_map<std::pair<uint32_t, uint32_t>, uint32_t> indexPairToFeatureIndexMap;
        compiledDataList->reserve(observationList.size());
        
        for (auto &obs : observationList) {
            compiledDataList->push_back(obs.compile(&labelToIndexMap, &attrToIndexMap, &indexPairToFeatureIndexMap, true));
        }
        std::vector<double> featureCountList(indexPairToFeatureIndexMap.size());
        for (auto &data : (*compiledDataList)) {
            data->accumulateFeatureCounts(featureCountList.data());
        }
        
        auto optimizer = std::make_shared<Optimizer::OptimizerClass>(maxEntUpdateProc, static_cast<void *>(&compiledDataList), std::move(featureCountList), concurrency, maxIters, useL1Regularization, regularizationCoefficient, epsilonForConvergence);
        std::vector<double> initialWeightList(featureCountList.size());
        optimizer->optimize(initialWeightList.data());
        auto bestWeightList = optimizer->getBestWeightList();
        
        modelData = std::make_shared<MaxEntData>(std::move(labelToIndexMap), std::move(attrToIndexMap), std::move(indexPairToFeatureIndexMap), std::move(bestWeightList));
    }

    std::string inferLabel(const Observation &obs) const {
        return obs.compile(&modelData->getLabelToIndexMap(), &modelData->getAttrToIndexMap(), &modelData->getIndexPairToFeatureIndexMap(), false)->inferLabel(modelData->getBestWeightList().data());
    }

    void writeModel(const std::string &filename) {
        modelData->trim();
        modelData->write(filename);
    }

    void readModel(const std::string &filename) {
        modelData->read(filename);
    }        
    
    std::shared_ptr<MaxEntData> modelData;
    std::shared_ptr<std::vector<double>> expWeightList;
    std::shared_ptr<std::vector<std::string>> labelStringList;
};

} // namespace MaxEnt

#endif // HOCRF_MAX_ENT_MAX_ENT_PROCESSOR_H_
