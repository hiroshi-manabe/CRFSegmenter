#ifndef HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_PROCESSOR_H_
#define HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_PROCESSOR_H_

#include "../task/task_queue.hpp"
#include "../Optimizer/OptimizerClass.h"
#include "types.h"
#include "PatternSetSequence.h"
#include "DataSequence.h"
#include "Feature.h"
#include "HighOrderCRFData.h"
#include "LabelSequence.h"
#include "ObservationSequence.h"

#include <cmath>
#include <cstdio>
#include <future>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace HighOrderCRF {

using std::future;
using std::make_pair;
using std::make_shared;
using std::move;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using Optimizer::OptimizerClass;

template<typename T> class FeatureTemplateGenerator;
class HighOrderCRFData;

double hocrfUpdateProc(void *updateData, const double *x, double *g, size_t concurrency) {
    auto sequenceList = static_cast<vector<shared_ptr<PatternSetSequence>> *>(updateData);
    
    hwm::task_queue tq(concurrency);
    vector<future<double>> futureList;

    for (auto &sequence : *sequenceList) {
        future<double> f = tq.enqueue([](shared_ptr<PatternSetSequence> pat, const double* expWeightArray, double* expectationArray) -> double {
                return pat->accumulateFeatureExpectations(expWeightArray, expectationArray);
            },
            sequence,
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

template<typename T> class HighOrderCRFProcessor
{
public:
    HighOrderCRFProcessor() : modelData(new HighOrderCRFData) {}
    void train(const vector<shared_ptr<ObservationSequence<T>>> &observationSequenceList,
               const FeatureTemplateGenerator<T> &featureTemplateGenerator,
               const unordered_set<string> &labelSet,
               size_t concurrency,
               size_t maxIter,
               bool useL1Regularization,
               double regularizationCoefficient,
               double epsilonForConvergence) {

        unordered_map<string, label_t> labelMap;
        label_t labelNum = 0;
        for (const auto &label : labelSet) {
            labelMap.insert(make_pair(label, labelNum));
            ++labelNum;
        }
        auto dataSequenceList = vector<shared_ptr<DataSequence>>();
        for (auto &observationSequence : observationSequenceList) {
            dataSequenceList.push_back(observationSequence->generateDataSequence(featureTemplateGenerator, labelMap));
        }
        
        unordered_map<shared_ptr<FeatureTemplate>, vector<uint32_t>> featureTemplateToFeatureIndexListMap;
        unordered_map<shared_ptr<Feature>, uint32_t> featureToFeatureIndexMap;
        vector<double> featureCountList;
        for (auto &dataSequence : dataSequenceList) {
            dataSequence->accumulateFeatureData(&featureTemplateToFeatureIndexListMap, &featureToFeatureIndexMap, &featureCountList);
        }

        unordered_map<shared_ptr<LabelSequence>, uint32_t> labelSequenceToIndexMap;
        vector<uint32_t> featureLabelSequenceIndexList(featureToFeatureIndexMap.size());
        vector<LabelSequence> labelSequenceList;

        for (auto &entry : featureToFeatureIndexMap) {
            const auto &f = entry.first;
            const auto &i = entry.second;
            auto seq = f->getLabelSequence();
            auto it = labelSequenceToIndexMap.find(seq);
            if (it == labelSequenceToIndexMap.end()) {
                it = labelSequenceToIndexMap.insert(make_pair(seq, labelSequenceToIndexMap.size())).first;
                labelSequenceList.emplace_back(*seq);  // copied
            }
            featureLabelSequenceIndexList[i] = it->second;
        }
        
        vector<shared_ptr<PatternSetSequence>> patternSetSequenceList;
        for (auto &dataSequence : dataSequenceList) {
            patternSetSequenceList.push_back(dataSequence->generatePatternSetSequence(featureTemplateToFeatureIndexListMap, featureLabelSequenceIndexList, labelSequenceList));
        }
        
        auto optimizer = make_shared<OptimizerClass>(hocrfUpdateProc, (void *)&patternSetSequenceList, featureCountList, concurrency, maxIter, useL1Regularization, regularizationCoefficient, epsilonForConvergence);
        auto initialWeightList = make_shared<vector<double>>(featureCountList.size());
        optimizer->optimize(initialWeightList->data());
        auto bestWeightList = optimizer->getBestWeightList();
        
        modelData = make_shared<HighOrderCRFData>(move(featureTemplateToFeatureIndexListMap), move(bestWeightList), move(featureLabelSequenceIndexList), move(labelSequenceList), move(labelMap));
    }

    shared_ptr<vector<string>> tag(const ObservationSequence<T> &observationSequence,
                                   const FeatureTemplateGenerator<T> &featureTemplateGenerator) {
        auto labelMap = modelData->getLabelMap();
        auto labelList = tagLabelType(observationSequence, &featureTemplateGenerator);
        auto ret = make_shared<vector<string>>();
        auto labelStringList = modelData->getLabelStringList();
        for (auto label : labelList) {
            ret->push_back(labelStringList[label]);
        }
        return ret;
    }
    
    void test(const vector<shared_ptr<ObservationSequence<T>>> &observationSequenceList,
              const FeatureTemplateGenerator<T> &featureTemplateGenerator,
              const vector<shared_ptr<vector<string>>> &correctLabelListList,
              size_t concurrency) {
        // number of distinct labels
        size_t labelCount = modelData->getLabelStringList().size();
        vector<size_t> observationLabelCounts(labelCount);
        vector<size_t> inferredLabelCounts(labelCount);
        vector<size_t> correctLabelCounts(labelCount);

        size_t correctSequenceCount = 0;
        size_t correctLabelCount = 0;
        size_t allLabelCount = 0;
        size_t sequenceCount = observationSequenceList.size();

        hwm::task_queue tq(concurrency);
        vector<future<vector<label_t>>> futureList;
        for (size_t i = 0 ; i < sequenceCount; ++i) {
            future<vector<label_t>> f = tq.enqueue(&HighOrderCRFProcessor::tagLabelType, this, *observationSequenceList[i], &featureTemplateGenerator);
            futureList.push_back(move(f));
        }

        for (size_t i = 0; i < sequenceCount; ++i) {
            auto &correctLabelList = correctLabelListList[i];
            auto inferredLabelList = futureList[i].get();
            bool isAllCorrect = true;
            for (size_t j = 0; j < correctLabelList->size(); ++j) {
                auto correctLabel = modelData->getLabelMap().at(correctLabelList->at(j));
                if (inferredLabelList[j] == correctLabel) {
                    ++correctLabelCounts[correctLabel];
                    ++correctLabelCount;
                }
                else {
                    isAllCorrect = false;
                }
                ++observationLabelCounts[correctLabel];
                ++inferredLabelCounts[inferredLabelList[j]];
                ++allLabelCount;
            }
            if (isAllCorrect) {
                ++correctSequenceCount;
            }
        }

        vector<double> precisionByLabel(labelCount);
        vector<double> recallByLabel(labelCount);
        vector<double> fMeasureByLabel(labelCount);

        for (size_t i = 0; i < labelCount; ++i) {
            precisionByLabel[i] = inferredLabelCounts[i] > 0 ? (correctLabelCounts[i] / (double)inferredLabelCounts[i]) : 0.0;
            recallByLabel[i] = observationLabelCounts[i] > 0 ? (correctLabelCounts[i] / (double)observationLabelCounts[i]) : 0.0;
            fMeasureByLabel[i] = (precisionByLabel[i] + recallByLabel[i] > 0) ? precisionByLabel[i] * recallByLabel[i] * 2 / (precisionByLabel[i] + recallByLabel[i]) : 0.0;
        }

        printf("Performance by label (#match, #model, #ref) (precision, recall, F1):\n");
        auto labelStringList = modelData->getLabelStringList();
        for (size_t i = 0; i < labelCount; ++i) {
            printf("    %s: (%d, %d, %d) (%1.4f, %1.4f, %1.4f)\n",
                labelStringList[i].c_str(),
                correctLabelCounts[i], inferredLabelCounts[i], observationLabelCounts[i],
                precisionByLabel[i], recallByLabel[i], fMeasureByLabel[i]);
        }
        printf("\n");
        printf("Item accuracy: %d / %d (%1.4f)\n",
            correctLabelCount, allLabelCount, correctLabelCount / (double)allLabelCount);
        printf("Instance Accuracy: %d / %d (%1.4f)\n",
            correctSequenceCount, sequenceCount, correctSequenceCount / (double)sequenceCount);

    }

    void writeModel(const string &filename) {
        modelData->trim();
        modelData->write(filename);
    }

    void readModel(const string &filename) {
        modelData->read(filename);
    }

private:
    // the second argument cannot be a simple reference because the task queue complains
    vector<label_t> tagLabelType(const ObservationSequence<T> &observationSequence,
                                 const FeatureTemplateGenerator<T> *featureTemplateGenerator) {
        auto dataSequence = observationSequence.generateDataSequence(*featureTemplateGenerator, modelData->getLabelMap());
        auto patternSetSequence = dataSequence->generatePatternSetSequence(modelData->getFeatureTemplateToFeatureIndexMapList(), modelData->getFeatureLabelSequenceIndexList(), modelData->getLabelSequenceList());
        return patternSetSequence->decode(modelData->getWeightList().data());
    }

    shared_ptr<HighOrderCRFData> modelData;
};

} // namespace HighOrderCRF

#endif // HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_PROCESSOR_H_
