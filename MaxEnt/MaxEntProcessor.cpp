#include "MaxEntProcessor.h"

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

using std::future;
using std::make_shared;
using std::move;
using std::pair;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

namespace MaxEnt {

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
        futureList.emplace_back(move(f));
    }
    tq.wait();

    double logLikelihood = 0.0;
    for (auto &f : futureList) {
        logLikelihood += f.get();
    }
    return logLikelihood;
}

MaxEntProcessor::MaxEntProcessor() : modelData(new MaxEntData) {}

void MaxEntProcessor::train(const vector<Observation> &observationList,
                            size_t concurrency,
                            size_t maxIters,
                            double regularizationCoefficientL1,
                            double regularizationCoefficientL2,
                            double epsilonForConvergence) {

    auto compiledDataList = make_shared<vector<shared_ptr<CompiledData>>>();
    unordered_map<string, uint32_t> labelToIndexMap;
    unordered_map<string, uint32_t> attrToIndexMap;
    unordered_map<pair<uint32_t, uint32_t>, uint32_t> indexPairToFeatureIndexMap;
    compiledDataList->reserve(observationList.size());
        
    for (auto &obs : observationList) {
        compiledDataList->emplace_back(obs.compile(&labelToIndexMap, &attrToIndexMap, &indexPairToFeatureIndexMap, true));
    }
    vector<double> featureCountList(indexPairToFeatureIndexMap.size());
    for (auto &data : (*compiledDataList)) {
        data->accumulateFeatureCounts(featureCountList.data());
    }
        
    auto optimizer = make_shared<Optimizer::OptimizerClass>(maxEntUpdateProc, static_cast<void *>(&compiledDataList), move(featureCountList), concurrency, maxIters, regularizationCoefficientL1, regularizationCoefficientL2, epsilonForConvergence);
    vector<double> initialWeightList(featureCountList.size());
    optimizer->optimize(initialWeightList.data());
    auto bestWeightList = optimizer->getBestWeightList();
        
    modelData = make_shared<MaxEntData>(move(labelToIndexMap), move(attrToIndexMap), move(indexPairToFeatureIndexMap), move(bestWeightList));
}

string MaxEntProcessor::inferLabel(const Observation &obs) const {
    return obs.compile(&modelData->getLabelToIndexMap(), &modelData->getAttrToIndexMap(), &modelData->getIndexPairToFeatureIndexMap(), false)->inferLabel(modelData->getBestWeightList().data());
}

void MaxEntProcessor::writeModel(const string &filename) {
    modelData->trim();
    modelData->write(filename);
}

void MaxEntProcessor::readModel(const string &filename) {
    modelData->read(filename);
}        
    
} // namespace MaxEnt
