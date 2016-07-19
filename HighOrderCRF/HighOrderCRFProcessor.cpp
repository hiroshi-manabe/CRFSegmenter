#include "HighOrderCRFProcessor.h"

#include "../task/task_queue.hpp"
#include "../Optimizer/OptimizerClass.h"
#include "types.h"
#include "PatternSetSequence.h"
#include "DataSequence.h"
#include "Feature.h"
#include "HighOrderCRFData.h"
#include "LabelSequence.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <future>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace HighOrderCRF {

using std::cerr;
using std::endl;
using std::future;
using std::getline;
using std::ifstream;
using std::istream;
using std::make_pair;
using std::make_shared;
using std::move;
using std::set;
using std::shared_ptr;
using std::stoi;
using std::string;
using std::stringstream;
using std::transform;
using std::unordered_map;
using std::vector;

using Optimizer::OptimizerClass;

vector<string> splitString(const string &s, char delim, int count = 0) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    int i = 0;
    while (getline(ss, item, (count && i >= count) ? '\0' : delim)) {
        elems.push_back(item);
        ++i;
    }
    return move(elems);
}

vector<string> readSequence(istream &is) {
    vector<string> ret;
    string line;
    while (getline(is, line) && !line.empty()) {
        ret.push_back(move(line));
    }
    return move(ret);
}

set<string> extractLabelSet(const vector<vector<string>> &seqList) {
    set<string> ret;
    for (const auto &seq : seqList) {
        for (const auto &str : seq) {
            auto fields = splitString(str, '\t');
            if (fields[0] != "*") {
                auto possibleLabels = splitString(fields[0], ',');
                ret.insert(possibleLabels.begin(), possibleLabels.end());
            }
            ret.insert(fields[1]);
        }
    }
    return move(ret);
}

shared_ptr<DataSequence> stringListToDataSequence(const vector<string> &seq, unordered_map<string, label_t> &labelMap, bool hasValidLabels) {
    vector<vector<shared_ptr<FeatureTemplate>>> featureTemplateListList;
    vector<label_t> labels;
    vector<unordered_set<label_t>> possibleLabelSetList;

    featureTemplateListList.reserve(seq.size());
    labels.reserve(seq.size());
    possibleLabelSetList.reserve(seq.size());

    for (const auto &str : seq) {
        auto fields = splitString(str, '\t');
        if (fields.size() < 3) {
            cerr << "Invalid input format: " << str << endl;
            exit(1);
        }
        
        if (fields[0] == "*") {
            possibleLabelSetList.emplace_back();
        }
        else {
            auto strLabels = splitString(fields[0], ',');
            unordered_set<label_t> possibleLabelSet;
            for (auto &strLabel : strLabels) {
                auto it = labelMap.find(strLabel);
                if (it != labelMap.end()) {
                    possibleLabelSet.insert(it->second);
                }
            }
            possibleLabelSetList.push_back(move(possibleLabelSet));
        }
        
        auto it = labelMap.find(fields[1]);
        if (it != labelMap.end()) {
            labels.push_back(it->second);
        }
        else {
            labels.push_back(INVALID_LABEL);
        }

        vector<shared_ptr<FeatureTemplate>> featureTemplateList;
        featureTemplateList.reserve(fields.size() - 2);
        for (auto it = fields.begin() + 2; it != fields.end(); ++it) {
            auto labelLengthAndTag = splitString(*it, ':', 2);
            if (labelLengthAndTag.size() != 2) {
                cerr << "Invalid field " << *it << endl;
                exit(1);
            }
            int labelLength = stoi(labelLengthAndTag[0]);
            if (labelLength < 1) {
                cerr << "Invalid label length: " << labelLengthAndTag[0] << endl;
                exit(1);
            }
            featureTemplateList.emplace_back(make_shared<FeatureTemplate>(labelLengthAndTag[1], labelLength));
        }
        featureTemplateListList.push_back(move(featureTemplateList));
    }
    return make_shared<DataSequence>(move(featureTemplateListList), move(labels), move(possibleLabelSetList), hasValidLabels);
}

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

HighOrderCRFProcessor::HighOrderCRFProcessor() : modelData(new HighOrderCRFData) {}

void HighOrderCRFProcessor::train(const string &filename,
                                  size_t concurrency,
                                  size_t maxIter,
                                  bool useL1Regularization,
                                  double regularizationCoefficient,
                                  double epsilonForConvergence) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cerr << "Cannot read from file: " << filename << endl;
        exit(1);
    }

    vector<vector<string>> seqList;
    while (true) {
        vector<string> seq = readSequence(ifs);
        if (ifs.eof()) {
            break;
        }
        seqList.push_back(move(seq));
    }
    ifs.close();

    auto labelSet = extractLabelSet(seqList);
    
    unordered_map<string, label_t> labelMap;
    label_t labelNum = 0;
    for (const auto &label : labelSet) {
        labelMap.insert(make_pair(label, labelNum));
        ++labelNum;
    }

    vector<shared_ptr<DataSequence>> dataSequenceList;
    dataSequenceList.reserve(seqList.size());

    for (const auto &seq : seqList) {
        dataSequenceList.push_back(stringListToDataSequence(seq, labelMap, true));
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

vector<string> HighOrderCRFProcessor::tag(const vector<string> &seq) const {
    auto labelMap = modelData->getLabelMap();
    auto dataSequence = stringListToDataSequence(seq, labelMap, false);
    auto labelList = tagLabelType(*dataSequence);
    vector<string> ret;
    auto labelStringList = modelData->getLabelStringList();
    for (auto label : labelList) {
        ret.push_back(labelStringList[label]);
    }
    return move(ret);
}

vector<string> HighOrderCRFProcessor::calcLabelLikelihoods(const vector<string> &seq) {
    prepareExpWeights();
    auto labelMap = modelData->getLabelMap();
    auto dataSequence = stringListToDataSequence(seq, labelMap, false);
    auto likelihoodMap = dataSequence
        ->generatePatternSetSequence(modelData->getFeatureTemplateToFeatureIndexMapList(), modelData->getFeatureLabelSequenceIndexList(), modelData->getLabelSequenceList())
        ->calcLabelLikelihoods(expWeights->data());
    auto labelStringList = modelData->getLabelStringList();
    vector<string> ret;
    ret.reserve(seq.size());
    for (const auto &m : likelihoodMap) {
        stringstream ss;
        bool isFirst = true;
        for (const auto &entry : m) {
            if (!isFirst) {
                ss << "\t";
            }
            ss << labelStringList[entry.first] << ":" << entry.second;
            isFirst = false;
        }
        ret.emplace_back(ss.str());
    }
    return move(ret);
}
    
void HighOrderCRFProcessor::test(const string &filename,
                                 size_t concurrency) const {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cerr << "Cannot read from file: " << filename << endl;
        exit(1);
    }

    vector<vector<string>> seqList;
    while (true) {
        vector<string> seq = readSequence(ifs);
        if (ifs.eof()) {
            break;
        }
        seqList.push_back(move(seq));
    }
    ifs.close();

    vector<shared_ptr<DataSequence>> dataSequenceList;
    dataSequenceList.reserve(seqList.size());

    auto labelMap = modelData->getLabelMap();

    for (const auto &seq : seqList) {
        dataSequenceList.push_back(stringListToDataSequence(seq, labelMap, true));
    }
        
    // number of distinct labels
    size_t labelCount = modelData->getLabelStringList().size();
    vector<size_t> dataLabelCounts(labelCount);
    vector<size_t> inferredLabelCounts(labelCount);
    vector<size_t> correctLabelCounts(labelCount);

    size_t correctSequenceCount = 0;
    size_t correctLabelCount = 0;
    size_t allLabelCount = 0;
    size_t sequenceCount = dataSequenceList.size();

    hwm::task_queue tq(concurrency);
    vector<future<vector<label_t>>> futureList;
    for (size_t i = 0 ; i < sequenceCount; ++i) {
        future<vector<label_t>> f = tq.enqueue(&HighOrderCRFProcessor::tagLabelType, this, *dataSequenceList[i]);
        futureList.push_back(move(f));
    }

    for (size_t i = 0; i < sequenceCount; ++i) {
        auto correctLabelList = dataSequenceList[i]->getAllLabels();
        auto inferredLabelList = futureList[i].get();
        bool isAllCorrect = true;
        for (size_t j = 0; j < correctLabelList.size(); ++j) {
            auto correctLabel = correctLabelList[i];
            if (inferredLabelList[j] == correctLabel) {
                ++correctLabelCounts[correctLabel];
                ++correctLabelCount;
            }
            else {
                isAllCorrect = false;
            }
            ++dataLabelCounts[correctLabel];
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
        recallByLabel[i] = dataLabelCounts[i] > 0 ? (correctLabelCounts[i] / (double)dataLabelCounts[i]) : 0.0;
        fMeasureByLabel[i] = (precisionByLabel[i] + recallByLabel[i] > 0) ? precisionByLabel[i] * recallByLabel[i] * 2 / (precisionByLabel[i] + recallByLabel[i]) : 0.0;
    }

    printf("Performance by label (#match, #model, #ref) (precision, recall, F1):\n");
    auto labelStringList = modelData->getLabelStringList();
    for (size_t i = 0; i < labelCount; ++i) {
        printf("    %s: (%d, %d, %d) (%1.4f, %1.4f, %1.4f)\n",
               labelStringList[i].c_str(),
               correctLabelCounts[i], inferredLabelCounts[i], dataLabelCounts[i],
               precisionByLabel[i], recallByLabel[i], fMeasureByLabel[i]);
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

vector<label_t> HighOrderCRFProcessor::tagLabelType(const DataSequence &dataSequence) const {
    return dataSequence
        .generatePatternSetSequence(modelData->getFeatureTemplateToFeatureIndexMapList(), modelData->getFeatureLabelSequenceIndexList(), modelData->getLabelSequenceList())
        ->decode(modelData->getWeightList().data());
}

void HighOrderCRFProcessor::prepareExpWeights() {
    if (expWeights || !modelData) {
        return;
    }
    expWeights.reset(new vector<double>());
    auto weightList = modelData->getWeightList();
    expWeights->reserve(weightList.size());
    for (auto w : weightList) {
        expWeights->push_back(exp(weight_to_double(w)));
    }
}

} // namespace HighOrderCRF
