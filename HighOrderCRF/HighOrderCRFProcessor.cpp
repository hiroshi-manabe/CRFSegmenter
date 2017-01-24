#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <future>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "HighOrderCRFProcessor.h"

#include "../task/task_queue.hpp"
#include "../Optimizer/OptimizerClass.h"
#include "types.h"
#include "PatternSetSequence.h"
#include "DataSequence.h"
#include "Feature.h"
#include "FeatureTemplate.h"
#include "HighOrderCRFData.h"
#include "InternalDataSequence.h"
#include "LabelSequence.h"

namespace HighOrderCRF {

using std::cerr;
using std::endl;
using std::future;
using std::ifstream;
using std::make_pair;
using std::make_shared;
using std::move;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using Optimizer::OptimizerClass;

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
        futureList.emplace_back(move(f));
    }
    tq.wait();

    double logLikelihood = 0.0;
    for (auto &f : futureList) {
        logLikelihood += f.get();
    }
    return logLikelihood;
}

HighOrderCRFProcessor::HighOrderCRFProcessor() : modelData(new HighOrderCRFData) {}

void HighOrderCRFProcessor::train(const string &filename,
                                  size_t concurrency,
                                  size_t maxIter,
                                  double regularizationCoefficientL1,
                                  double regularizationCoefficientL2,
                                  double epsilonForConvergence) {
    ifstream ifs_label(filename);
    if (!ifs_label.is_open()) {
        cerr << "Cannot read from file: " << filename << endl;
        exit(1);
    }

    size_t count = 0;
    unordered_set<string> labelSet;
    while (true) {
        DataSequence seq(ifs_label);
        if (seq.empty()) {
            break;
        }
        auto s = seq.getUsedLabelSet();
        labelSet.insert(s.begin(), s.end());
        ++count;
    }
    ifs_label.close();

    unordered_map<string, label_t> labelMap;
    label_t labelNum = 0;
    for (const auto &label : labelSet) {
        labelMap.insert(make_pair(label, labelNum));
        ++labelNum;
    }

    ifstream ifs(filename);
    vector<InternalDataSequence> internalDataSequenceList;
    internalDataSequenceList.reserve(count);
    while (true) {
        DataSequence seq(ifs);
        if (seq.empty()) {
            break;
        }
        internalDataSequenceList.emplace_back(seq.toInternalDataSequence(labelMap));
    }
    ifs.close();
    
    unordered_map<FeatureTemplate, vector<uint32_t>> featureTemplateToFeatureIndexListMap;
    unordered_map<Feature, uint32_t> featureToFeatureIndexMap;
    vector<double> featureCountList;
    for (auto &internalDataSequence : internalDataSequenceList) {
        internalDataSequence.accumulateFeatureData(&featureTemplateToFeatureIndexListMap, &featureToFeatureIndexMap, &featureCountList);
    }

    unordered_map<LabelSequence, uint32_t> labelSequenceToIndexMap;
    vector<uint32_t> featureLabelSequenceIndexList(featureToFeatureIndexMap.size());
    vector<LabelSequence> labelSequenceList;

    for (auto &entry : featureToFeatureIndexMap) {
        const auto &f = entry.first;
        const auto &i = entry.second;
        const auto seq = f.getLabelSequence();
        auto it = labelSequenceToIndexMap.find(seq);
        if (it == labelSequenceToIndexMap.end()) {
            it = labelSequenceToIndexMap.insert(make_pair(seq, labelSequenceToIndexMap.size())).first;
            labelSequenceList.emplace_back(seq);  // copied
        }
        featureLabelSequenceIndexList[i] = it->second;
    }
        
    vector<shared_ptr<PatternSetSequence>> patternSetSequenceList;
    for (auto &internalDataSequence : internalDataSequenceList) {
        patternSetSequenceList.emplace_back(internalDataSequence.generatePatternSetSequence(featureTemplateToFeatureIndexListMap, featureLabelSequenceIndexList, labelSequenceList, true));
    }
    // free memory
    vector<InternalDataSequence>().swap(internalDataSequenceList);
        
    auto optimizer = make_shared<OptimizerClass>(hocrfUpdateProc, (void *)&patternSetSequenceList, featureCountList, concurrency, maxIter, regularizationCoefficientL1, regularizationCoefficientL2, epsilonForConvergence);
    auto initialWeightList = make_shared<vector<double>>(featureCountList.size());
    optimizer->optimize(initialWeightList->data());
    auto bestWeightList = optimizer->getBestWeightList();
        
    modelData = make_shared<HighOrderCRFData>(move(featureTemplateToFeatureIndexListMap), move(bestWeightList), move(featureLabelSequenceIndexList), move(labelSequenceList), move(labelMap));
}

void HighOrderCRFProcessor::test(const string &filename,
                                 size_t concurrency) const {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cerr << "Cannot read from file: " << filename << endl;
        exit(1);
    }

    vector<DataSequence> seqList;
    while (true) {
        DataSequence seq(ifs);
        if (seq.empty()) {
            break;
        }
        seqList.emplace_back(seq);
    }
    ifs.close();

    unordered_map<string, size_t> dataLabelCountMap;
    unordered_map<string, size_t> inferredLabelCountMap;
    unordered_map<string, size_t> correctLabelCountMap;

    size_t correctSequenceCount = 0;
    size_t correctLabelCount = 0;
    size_t allLabelCount = 0;
    size_t sequenceCount = seqList.size();

    vector<vector<string>> correctLabelListList;
    correctLabelListList.reserve(sequenceCount);

    hwm::task_queue tq(concurrency);
    vector<future<vector<string>>> futureList;
    for (size_t i = 0 ; i < sequenceCount; ++i) {
        // copies the correct labels
        correctLabelListList.emplace_back(seqList[i].getLabels());
        future<vector<string>> f = tq.enqueue(&HighOrderCRFProcessor::tag, this, &seqList[i]);
        futureList.emplace_back(move(f));
    }

    for (size_t i = 0; i < sequenceCount; ++i) {
        const auto &correctLabelList = correctLabelListList[i];
        auto inferredLabelList = futureList[i].get();
        bool isAllCorrect = true;
        for (size_t j = 0; j < correctLabelList.size(); ++j) {
            auto correctLabel = correctLabelList[j];
            if (inferredLabelList[j] == correctLabel) {
                ++correctLabelCountMap[correctLabel];
                ++correctLabelCount;
            }
            else {
                isAllCorrect = false;
            }
            ++dataLabelCountMap[correctLabel];
            ++inferredLabelCountMap[inferredLabelList[j]];
            ++allLabelCount;
        }
        if (isAllCorrect) {
            ++correctSequenceCount;
        }
    }

    unordered_map<string, double> precisionByLabel;
    unordered_map<string, double> recallByLabel;
    unordered_map<string, double> fMeasureByLabel;

    auto labelMap = modelData->getLabelMap();
    for (const auto &entry : labelMap) {
        const auto &key = entry.first;
        precisionByLabel[key] = inferredLabelCountMap[key] > 0 ? (correctLabelCountMap[key] / (double)inferredLabelCountMap[key]) : 0.0;
        recallByLabel[key] = dataLabelCountMap[key] > 0 ? (correctLabelCountMap[key] / (double)dataLabelCountMap[key]) : 0.0;
        fMeasureByLabel[key] = (precisionByLabel[key] + recallByLabel[key] > 0) ? precisionByLabel[key] * recallByLabel[key] * 2 / (precisionByLabel[key] + recallByLabel[key]) : 0.0;
    }

    printf("Performance by label (#match, #model, #ref) (precision, recall, F1):\n");
    for (const auto &entry : labelMap) {
        const auto &key = entry.first;
        printf("    %s: (%d, %d, %d) (%1.4f, %1.4f, %1.4f)\n",
               key.c_str(),
               correctLabelCountMap[key], inferredLabelCountMap[key], dataLabelCountMap[key],
               precisionByLabel[key], recallByLabel[key], fMeasureByLabel[key]);
    }
    printf("\n");
    printf("Item accuracy: %d / %d (%1.4f)\n",
           correctLabelCount, allLabelCount, correctLabelCount / (double)allLabelCount);
    printf("Instance Accuracy: %d / %d (%1.4f)\n",
           correctSequenceCount, sequenceCount, correctSequenceCount / (double)sequenceCount);
}

void HighOrderCRFProcessor::writeModel(const string &filename) {
    modelData->trim();
    modelData->write(filename);
}

void HighOrderCRFProcessor::readModel(const string &filename) {
    modelData->read(filename);
}

vector<string> HighOrderCRFProcessor::tag(DataSequence *dataSequence) const {
    vector<string> ret;
    if (dataSequence->empty()) {
        return ret;
    }
    auto labelStringList = modelData->getLabelStringList();
    auto l = dataSequence
        ->toInternalDataSequence(modelData->getLabelMap())
        .generatePatternSetSequence(modelData->getFeatureTemplateToFeatureIndexMapList(), modelData->getFeatureLabelSequenceIndexList(), modelData->getLabelSequenceList(), false)
        ->decode(modelData->getWeightList().data());
    ret.reserve(l.size());
    for (auto label : l) {
        ret.emplace_back(labelStringList[label]);
    }
    return ret;
}

vector<unordered_map<string, double>> HighOrderCRFProcessor::calcLabelLikelihoods(DataSequence *dataSequence) const {
    vector<unordered_map<string, double>> ret;
    if (dataSequence->empty()) {
        return ret;
    }
    auto labelStringList = modelData->getLabelStringList();
    auto v = dataSequence
        ->toInternalDataSequence(modelData->getLabelMap())
        .generatePatternSetSequence(modelData->getFeatureTemplateToFeatureIndexMapList(), modelData->getFeatureLabelSequenceIndexList(), modelData->getLabelSequenceList(), false)
        ->calcLabelLikelihoods(modelData->getExpWeightList().data());
    ret.reserve(v.size());
    for (const auto &m : v) {
        unordered_map<string, double> newMap;
        for (const auto &entry : m) {
            newMap.insert(make_pair(labelStringList[entry.first], entry.second));
        }
    }
    return ret;
}

} // namespace HighOrderCRF
