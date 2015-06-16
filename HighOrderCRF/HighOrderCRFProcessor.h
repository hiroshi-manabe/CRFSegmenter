#ifndef HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_PROCESSOR_H_
#define HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_PROCESSOR_H_

#include "types.h"
#include "../task/task_queue.hpp"
#include "PatternSetSequence.h"
#include "DataSequence.h"
#include "Feature.h"
#include "HighOrderCRFData.h"
#include "LabelSequence.h"
#include "../Optimizer/OptimizerClass.h"
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
    auto sequenceList = static_cast<shared_ptr<vector<shared_ptr<PatternSetSequence>>> *>(updateData);
    
    hwm::task_queue tq(concurrency);
    vector<future<double>> futureList;

    for (auto &sequence : **sequenceList) {
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
    void train(shared_ptr<vector<shared_ptr<ObservationSequence<T>>>> observationSequenceList,
               shared_ptr<FeatureTemplateGenerator<T>> featureTemplateGenerator,
               shared_ptr<unordered_set<string>> labelSet,
               size_t concurrency,
               size_t maxIter,
               bool useL1Regularization,
               double regularizationCoefficient,
               double epsilonForConvergence) {

        auto labelMap = make_shared<unordered_map<string, label_t>>();
        label_t labelNum = 0;
        for (const auto &label : *labelSet) {
            labelMap->insert(make_pair(label, labelNum));
            ++labelNum;
        }
        auto dataSequenceList = make_shared<vector<shared_ptr<DataSequence>>>();
        for (auto &observationSequence : *observationSequenceList) {
            dataSequenceList->push_back(observationSequence->generateDataSequence(featureTemplateGenerator, labelMap));
        }
        auto featureToFeatureCountMap = make_shared<unordered_map<shared_ptr<Feature>, size_t>>();
        for (auto &dataSequence : *dataSequenceList) {
            dataSequence->accumulateFeatureCountsToMap(featureToFeatureCountMap);
        }
        auto featureList = make_shared<vector<Feature>>();
        auto featureCountList = make_shared<vector<double>>(featureToFeatureCountMap->size());
        auto featureTemplateToFeatureListMap = make_shared<unordered_map<shared_ptr<FeatureTemplate>, shared_ptr<vector<const Feature *>>>>();
        
        feature_index_t featureIndex = 0;
        for (auto &entry : *featureToFeatureCountMap) {
            auto &feature = entry.first;
            featureList->push_back(move(*feature));
            (*featureCountList)[featureIndex] = entry.second;
            ++featureIndex;
            auto ft = feature->createFeatureTemplate();
            if (featureTemplateToFeatureListMap->find(ft) == featureTemplateToFeatureListMap->end()) {
                featureTemplateToFeatureListMap->insert(make_pair(ft, make_shared<vector<const Feature *>>()));
            }
            featureTemplateToFeatureListMap->at(ft)->push_back(&featureList->back());
        }

        auto patternSetSequenceList = make_shared<vector<shared_ptr<PatternSetSequence>>>();
        for (auto &dataSequence : *dataSequenceList) {
            patternSetSequenceList->push_back(dataSequence->generatePatternSetSequence(featureTemplateToFeatureListMap, &featureList->front()));
        }
        auto optimizer = make_shared<OptimizerClass>(hocrfUpdateProc, (void *)&patternSetSequenceList, featureCountList, concurrency, maxIter, useL1Regularization, regularizationCoefficient, epsilonForConvergence);
        auto initialWeightList = make_shared<vector<double>>(featureList->size());
        optimizer->optimize(initialWeightList->data());
        auto bestWeightList = optimizer->getBestWeightList();
        
        modelData = make_shared<HighOrderCRFData>(featureList, bestWeightList, labelMap);
    }

    shared_ptr<vector<string>> tag(shared_ptr<ObservationSequence<T>> observationSequence,
                                   shared_ptr<FeatureTemplateGenerator<T>> featureTemplateGenerator) {
        auto labelMap = modelData->getLabelMap();
        auto labelList = tagLabelType(observationSequence, featureTemplateGenerator, &modelData->getFeatureList()->front());
        auto ret = make_shared<vector<string>>();
        for (auto label : *labelList) {
            ret->push_back((*labelStringList)[label]);
        }
        return ret;
    }
    
    void test(shared_ptr<vector<shared_ptr<ObservationSequence<T>>>> observationSequenceList,
              shared_ptr<FeatureTemplateGenerator<T>> featureTemplateGenerator,
              shared_ptr<vector<shared_ptr<vector<string>>>> correctLabelListList,
              size_t concurrency) {
        // number of distinct labels
        size_t labelCount = modelData->getLabelStringList()->size();
        vector<size_t> observationLabelCounts(labelCount);
        vector<size_t> inferredLabelCounts(labelCount);
        vector<size_t> correctLabelCounts(labelCount);

        size_t correctSequenceCount = 0;
        size_t correctLabelCount = 0;
        size_t allLabelCount = 0;
        size_t sequenceCount = observationSequenceList->size();

        hwm::task_queue tq(concurrency);
        vector<future<shared_ptr<vector<label_t>>>> futureList;
        for (size_t i = 0 ; i < sequenceCount; ++i) {
            future<shared_ptr<vector<label_t>>> f = tq.enqueue(&HighOrderCRFProcessor::tagLabelType, this, observationSequenceList->at(i), featureTemplateGenerator, &modelData->getFeatureList()->front());
            futureList.push_back(move(f));
        }

        for (size_t i = 0; i < sequenceCount; ++i) {
            auto &correctLabelList = correctLabelListList->at(i);
            auto inferredLabelList = futureList[i].get();
            bool isAllCorrect = true;
            for (size_t j = 0; j < correctLabelList->size(); ++j) {
                auto correctLabel = modelData->getLabelMap()->at(correctLabelList->at(j));
                if (inferredLabelList->at(j) == correctLabel) {
                    ++correctLabelCounts[correctLabel];
                    ++correctLabelCount;
                }
                else {
                    isAllCorrect = false;
                }
                ++observationLabelCounts[correctLabel];
                ++inferredLabelCounts[inferredLabelList->at(j)];
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
        for (size_t i = 0; i < labelCount; ++i) {
            printf("    %s: (%d, %d, %d) (%1.4f, %1.4f, %1.4f)\n",
                labelStringList->at(i).c_str(),
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
        modelData->write(filename);
    }

    void readModel(const string &filename) {
        modelData->read(filename);
        prepare();
    }

private:
    shared_ptr<vector<label_t>> tagLabelType(shared_ptr<ObservationSequence<T>> observationSequence,
                                             shared_ptr<FeatureTemplateGenerator<T>> featureTemplateGenerator,
                                             const Feature *firstFeature) {
        auto dataSequence = observationSequence->generateDataSequence(featureTemplateGenerator, modelData->getLabelMap());
        auto patternSetSequence = dataSequence->generatePatternSetSequence(featureTemplateToFeatureListMap, firstFeature);
        return patternSetSequence->decode(expWeightList.get()->data());
    }

    void prepare() {
        auto featureCount = modelData->getBestWeightList()->size();
        expWeightList = make_shared<vector<double>>(featureCount);
        for (size_t i = 0; i < featureCount; ++i) {
            (*expWeightList)[i] = exp((*modelData->getBestWeightList())[i]);
        }
        featureTemplateToFeatureListMap = make_shared<unordered_map<shared_ptr<FeatureTemplate>, shared_ptr<vector<const Feature *>>>>();
        for (auto &feature : *modelData->getFeatureList()) {
            auto ft = feature.createFeatureTemplate();
            if (featureTemplateToFeatureListMap->find(ft) == featureTemplateToFeatureListMap->end()) {
                featureTemplateToFeatureListMap->insert(make_pair(ft, make_shared<vector<const Feature *>>()));
            }
            featureTemplateToFeatureListMap->at(ft)->push_back(&feature);
        }
        labelStringList = modelData->getLabelStringList();
    }
    shared_ptr<HighOrderCRFData> modelData;
    shared_ptr<unordered_map<shared_ptr<FeatureTemplate>, shared_ptr<vector<const Feature *>>>> featureTemplateToFeatureListMap;
    shared_ptr<vector<double>> expWeightList;
    shared_ptr<vector<string>> labelStringList;
};

} // namespace HighOrderCRF

#endif // HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_PROCESSOR_H_
