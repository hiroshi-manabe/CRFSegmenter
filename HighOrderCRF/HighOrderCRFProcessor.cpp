#include <algorithm>
#include <cassert>
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
#include "HighOrderCRFData.h"
#include "LabelSequence.h"

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
using std::unordered_map;
using std::unordered_set;
using std::vector;

using Optimizer::OptimizerClass;

vector<string> splitString(const string &s, char delim = '\t', int count = 0) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    int i = 1;
    while (getline(ss, item, (count && i >= count) ? '\0' : delim)) {
        elems.push_back(item);
        ++i;
    }
    return elems;
}

static void outputFields(const vector<string> &fields) {
    bool isFirst = true;
    for (const auto &field : fields) {
        if (!isFirst) {
            cerr << "\t";
        }
        cerr << field;
        isFirst = false;
    }
}

static vector<vector<string>> readSequence(istream &is) {
    vector<vector<string>> ret;
    string line;
    while (getline(is, line) && !line.empty()) {
        auto fields = splitString(line);
            if (fields.size() < 4) {
            cerr << "Invalid input format: ";
            outputFields(fields);
            exit(1);
        }
        ret.emplace_back(move(fields));
    }
    return ret;
}

static set<string> extractLabelSet(const vector<vector<vector<string>>> &seqList) {
    set<string> ret;
    for (const auto &seq : seqList) {
        for (const auto &fields : seq) {
            if (fields[1] != "*") {
                auto possibleLabels = splitString(fields[1], ',');
                ret.insert(possibleLabels.begin(), possibleLabels.end());
            }
            ret.insert(fields[2]);
        }
    }
    return ret;
}

static shared_ptr<DataSequence> stringListListToDataSequence(
    const vector<vector<string>> &seq,
    unordered_map<string, label_t> &labelMap,
    bool hasValidLabels) {

    vector<vector<shared_ptr<FeatureTemplate>>> featureTemplateListList;
    vector<label_t> labels;
    vector<unordered_set<label_t>> possibleLabelSetList;

    featureTemplateListList.reserve(seq.size());
    labels.reserve(seq.size());
    possibleLabelSetList.reserve(seq.size());

    for (const auto &fields : seq) {
        auto it = labelMap.find(fields[2]);
        if (it != labelMap.end()) {
            labels.push_back(it->second);
        }
        else {
            labels.push_back(INVALID_LABEL);
        }

        if (fields[1] == "*") {
            possibleLabelSetList.emplace_back();
        }
        else {
            auto strLabels = splitString(fields[1], ',');
            unordered_set<label_t> possibleLabelSet;
            for (auto &strLabel : strLabels) {
                auto it = labelMap.find(strLabel);
                if (it != labelMap.end()) {
                    possibleLabelSet.insert(it->second);
                }
            }
            if (hasValidLabels &&
                possibleLabelSet.find(labels.back()) == possibleLabelSet.end()) {
                cerr << "Correct label \"" << labels.back()
                     << "\" is not included in the possible label set: ";
                outputFields(fields);
                exit(1);
            }
            possibleLabelSetList.push_back(move(possibleLabelSet));
        }
        
        vector<shared_ptr<FeatureTemplate>> featureTemplateList;
        featureTemplateList.reserve(fields.size() - 3);
        for (auto it = fields.begin() + 3; it != fields.end(); ++it) {
            auto labelLengthAndTag = splitString(*it, ':', 2);
            if (labelLengthAndTag.size() != 2) {
                cerr << "Invalid field :" << *it << endl;
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
                                  double regularizationCoefficientL1,
                                  double regularizationCoefficientL2,
                                  double epsilonForConvergence) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cerr << "Cannot read from file: " << filename << endl;
        exit(1);
    }

    vector<vector<vector<string>>> seqList;
    while (true) {
        vector<vector<string>> seq = readSequence(ifs);
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
    vector<string> dummy;

    for (const auto &seq : seqList) {
        dataSequenceList.push_back(stringListListToDataSequence(seq, labelMap, true));
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
        
    auto optimizer = make_shared<OptimizerClass>(hocrfUpdateProc, (void *)&patternSetSequenceList, featureCountList, concurrency, maxIter, regularizationCoefficientL1, regularizationCoefficientL2, epsilonForConvergence);
    auto initialWeightList = make_shared<vector<double>>(featureCountList.size());
    optimizer->optimize(initialWeightList->data());
    auto bestWeightList = optimizer->getBestWeightList();
        
    modelData = make_shared<HighOrderCRFData>(move(featureTemplateToFeatureIndexListMap), move(bestWeightList), move(featureLabelSequenceIndexList), move(labelSequenceList), move(labelMap));
}

vector<string> HighOrderCRFProcessor::tag(const vector<vector<string>> &seq) const {
    vector<string> ret;
    if (seq.empty()) {
        return ret;
    }
    auto labelMap = modelData->getLabelMap();
    auto dataSequence = stringListListToDataSequence(seq, labelMap, false);
    auto labelList = tagLabelType(*dataSequence);
    auto labelStringList = modelData->getLabelStringList();
    for (size_t i = 0; i < labelList.size(); ++i) {
        ret.push_back(seq[i][0] + "\t" + labelStringList[labelList[i]]);
    }
    return ret;
}

vector<string> HighOrderCRFProcessor::calcLabelLikelihoods(const vector<vector<string>> &seq) {
    vector<string> ret;
    if (seq.empty()) {
        return ret;
    }
    prepareExpWeights();
    auto labelMap = modelData->getLabelMap();
    vector<string> dummy;
    auto dataSequence = stringListListToDataSequence(seq, labelMap, false);
    auto likelihoodMapList = dataSequence
        ->generatePatternSetSequence(modelData->getFeatureTemplateToFeatureIndexMapList(), modelData->getFeatureLabelSequenceIndexList(), modelData->getLabelSequenceList())
        ->calcLabelLikelihoods(expWeights->data());
    auto labelStringList = modelData->getLabelStringList();
    ret.reserve(seq.size());
    for (size_t i = 0; i < seq.size(); ++i) {
        stringstream ss;
        ss << seq[i][0] << "\t";
        for (const auto &entry : likelihoodMapList[i]) {
            ss << "\t";
            ss << labelStringList[entry.first] << ":" << entry.second;
        }
        ret.emplace_back(ss.str());
    }
    return ret;
}
    
void HighOrderCRFProcessor::test(const string &filename,
                                 size_t concurrency) const {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cerr << "Cannot read from file: " << filename << endl;
        exit(1);
    }

    vector<vector<vector<string>>> seqList;
    while (true) {
        vector<vector<string>> seq = readSequence(ifs);
        if (ifs.eof()) {
            break;
        }
        seqList.push_back(move(seq));
    }
    ifs.close();

    vector<shared_ptr<DataSequence>> dataSequenceList;
    dataSequenceList.reserve(seqList.size());

    auto labelMap = modelData->getLabelMap();
    vector<string> dummy;

    for (const auto &seq : seqList) {
        dataSequenceList.push_back(stringListListToDataSequence(seq, labelMap, true));
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
            auto correctLabel = correctLabelList[j];
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
