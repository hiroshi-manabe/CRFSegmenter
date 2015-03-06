#ifndef HOCRF_HIGH_ORDER_CRF_H_
#define HOCRF_HIGH_ORDER_CRF_H_

#include "types.h"
#include "../task/task_queue.hpp"
#include "CompactPatternSetSequence.h"
#include "DataSequence.h"
#include "Feature.h"
#include "HighOrderCRFData.h"
#include "LabelSequence.h"
#include "Optimizer.h"
#include "ObservationSequence.h"
#include "ObservationSet.h"

#include <cmath>
#include <cstdio>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#ifdef CRFSUITE_OUTPUT
#include <fstream>
using std::endl;
using std::ofstream;
#endif

namespace HighOrderCRF {

using std::future;
using std::make_shared;
using std::move;
using std::pair;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

template<typename T> class FeatureTemplateGenerator;
class HighOrderCRFData;

template<typename T> class HighOrderCRFProcessor
{
public:
    HighOrderCRFProcessor() : modelData(new HighOrderCRFData) {}
    void train(shared_ptr<vector<shared_ptr<ObservationSequence<T>>>> observationSequenceList,
               shared_ptr<FeatureTemplateGenerator<T>> featureTemplateGenerator,
               size_t concurrency,
               size_t maxIters,
               bool useL1Regularization,
               double regularizationCoefficient,
               double epsilonForConvergence) {

        auto observationSet = make_shared<ObservationSet<T>>(observationSequenceList);
        auto labelMap = observationSet->generateLabelMap();
        auto dataSequenceList = make_shared<vector<shared_ptr<DataSequence>>>();
        for (auto &observationSequence : *observationSequenceList) {
            dataSequenceList->push_back(observationSequence->generateDataSequence(featureTemplateGenerator, labelMap));
        }
        auto featureToFeatureCountMap = make_shared<unordered_map<shared_ptr<Feature>, size_t>>();
        for (auto &dataSequence : *dataSequenceList) {
            dataSequence->accumulateFeatureCountsToMap(featureToFeatureCountMap);
        }
        auto featureList = make_shared<vector<shared_ptr<Feature>>>();
        auto featureCountList = make_shared<vector<double>>(featureToFeatureCountMap->size());
        auto featureTemplateToFeatureListMap = make_shared<unordered_map<shared_ptr<FeatureTemplate>, shared_ptr<vector<shared_ptr<Feature>>>>>();
        
        feature_index_t featureIndex = 0;
        for (auto &entry : *featureToFeatureCountMap) {
            auto &feature = entry.first;
            feature->setIndex(featureIndex);
            featureList->push_back(feature);
            (*featureCountList)[featureIndex] = entry.second;
            ++featureIndex;
            auto ft = feature->createFeatureTemplate();
            if (featureTemplateToFeatureListMap->find(ft) == featureTemplateToFeatureListMap->end()) {
                featureTemplateToFeatureListMap->insert(pair<shared_ptr<FeatureTemplate>, shared_ptr<vector<shared_ptr<Feature>>>>(ft, make_shared<vector<shared_ptr<Feature>>>()));
            }
            featureTemplateToFeatureListMap->at(ft)->push_back(feature);
        }

#ifdef CRFSUITE_OUTPUT
        ofstream ofs("crfsuite.data", std::ios::binary);
        for (auto &observationSequence : *observationSequenceList) {
            ofs << observationSequence->generateCRFSuiteData(featureTemplateGenerator);
        }
        ofs.close();
#endif
        auto compactPatternSetSequenceList = make_shared<vector<shared_ptr<CompactPatternSetSequence>>>();
        for (auto &dataSequence : *dataSequenceList) {
            compactPatternSetSequenceList->push_back(dataSequence->generateCompactPatternSetSequence(featureTemplateToFeatureListMap));
        }
        auto optimizer = make_shared<Optimizer>(compactPatternSetSequenceList, featureCountList, concurrency, 0, false, regularizationCoefficient, epsilonForConvergence);
        auto initialWeightList = make_shared<vector<double>>(featureList->size());
        optimizer->optimize(initialWeightList->data());
        auto bestWeightList = optimizer->getBestWeightList();
        
        auto featureListToSave = make_shared<vector<shared_ptr<Feature>>>();
        auto bestWeightListToSave = make_shared<vector<double>>();
        for (size_t i = 0; i < featureList->size(); ++i) {
            auto &feature = (*featureList)[i];
            if (1 || (*bestWeightList)[i] != 0.0 || (feature->getObservation().empty() && feature->getLabelSequence()->getLength() == 1)) {
                featureListToSave->push_back(feature);
                bestWeightListToSave->push_back((*bestWeightList)[i]);
            }
        }
        modelData = make_shared<HighOrderCRFData>(featureListToSave, bestWeightListToSave, labelMap);
#ifdef CRFSUITE_OUTPUT
        modelData->dumpFeatures("features.txt", false);
#endif
        prepare();
    }

    shared_ptr<vector<string>> tag(shared_ptr<ObservationSequence<T>> observationSequence,
        shared_ptr<FeatureTemplateGenerator<T>> featureTemplateGenerator) {
        auto labelList = tagLabelType(observationSequence, featureTemplateGenerator);
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
            future<shared_ptr<vector<label_t>>> f = tq.enqueue(&HighOrderCRFProcessor::tagLabelType, this, observationSequenceList->at(i), featureTemplateGenerator);
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
            printf("    %s: (%d, %d, %d) (%1.4f, %1.4f, %1.4f\n",
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
        shared_ptr<FeatureTemplateGenerator<T>> featureTemplateGenerator) {
        auto dataSequence = observationSequence->generateDataSequence(featureTemplateGenerator, modelData->getLabelMap());
        auto compactPatternSetSequence = dataSequence->generateCompactPatternSetSequence(featureTemplateToFeatureListMap);
        return compactPatternSetSequence->decode(expWeightList.get()->data());
    }

    void prepare() {
        auto featureCount = modelData->getBestWeightList()->size();
        expWeightList = make_shared<vector<double>>(featureCount);
        for (size_t i = 0; i < featureCount; ++i) {
            (*expWeightList)[i] = exp((*modelData->getBestWeightList())[i]);
        }
        featureTemplateToFeatureListMap = make_shared<unordered_map<shared_ptr<FeatureTemplate>, shared_ptr<vector<shared_ptr<Feature>>>>>();
        for (auto &feature : *modelData->getFeatureList()) {
            auto ft = feature->createFeatureTemplate();
            if (featureTemplateToFeatureListMap->find(ft) == featureTemplateToFeatureListMap->end()) {
                featureTemplateToFeatureListMap->insert(pair<shared_ptr<FeatureTemplate>, shared_ptr<vector<shared_ptr<Feature>>>>(ft, make_shared<vector<shared_ptr<Feature>>>()));
            }
            featureTemplateToFeatureListMap->at(ft)->push_back(feature);
        }
        labelStringList = modelData->getLabelStringList();
    }
    shared_ptr<HighOrderCRFData> modelData;
    shared_ptr<unordered_map<shared_ptr<FeatureTemplate>, shared_ptr<vector<shared_ptr<Feature>>>>> featureTemplateToFeatureListMap;
    shared_ptr<vector<double>> expWeightList;
    shared_ptr<vector<string>> labelStringList;
};

} // namespace HighOrderCRF

#endif // HOCRF_HIGH_ORDER_CRF_H_

