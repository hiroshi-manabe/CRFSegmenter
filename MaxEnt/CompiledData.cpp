#ifndef HOCRF_MAX_ENT_OBSERVATION_H_
#define HOCRF_MAX_ENT_OBSERVATION_H_

#include "CompiledData.h"

#include <cassert>
#include <cmath>
#include <limits>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace MaxEnt {

using std::mutex;
using std::numeric_limits;
using std::shared_ptr;
using std::string;
using std::vector;

CompiledData::CompiledData(vector<vector<size_t>> featureIndexListList,
                           vector<string> labelStringList,
                           size_t correctLabelIndex) {
    assert(featureIndexListList.size() == labelStringList.size());
    assert(correctLabelIndex < labelStringList.size());
    this->featureIndexListList = featureIndexListList;
    this->labelStringList = labelStringList;
    this->correctLabelIndex = correctLabelIndex;
}

void CompiledData::accumulateFeatureCounts(double *counts) const {
    for (size_t featureIndex : featureIndexListList[correctLabelIndex]) {
        counts[featureIndex] += 1.0;
    }
}

static mutex expectationMutex;
// returns log likelihood of the sequence
double CompiledData::accumulateFeatureExpectations(const double *expWeights, double *expectations) const {
    size_t labelCount = featureIndexListList.size();
    double sum = 0.0;
    vector<double> scoreList(labelCount);
    for (size_t labelIndex = 0; labelIndex < featureIndexListList.size(); ++labelIndex) {
        scoreList[labelIndex] = 1.0;
        for (size_t featureIndex : featureIndexListList[labelIndex]) {
            scoreList[labelIndex] *= expWeights[featureIndex];
        }
        sum += scoreList[labelIndex];
    }
    for (size_t labelIndex = 0; labelIndex < featureIndexListList.size(); ++labelIndex) {
        double prob = scoreList[labelIndex] / sum;
        expectationMutex.lock();
        for (size_t featureIndex : featureIndexListList[labelIndex]) {
            expectations[featureIndex] += prob;
        }
        expectationMutex.unlock();
    }
    return log(scoreList[correctLabelIndex] / sum);
}

const string &CompiledData::inferLabel(const double *weights) const {
    double maxScore = numeric_limits<double>::lowest();
    size_t bestLabelIndex = 0;
    for (size_t labelIndex = 0; labelIndex < featureIndexListList.size(); ++labelIndex) {
        auto &featureIndexList = featureIndexListList[labelIndex];
        double score = 0.0;
        for (size_t featureIndex : featureIndexList) {
            score += weights[featureIndex];
        }
        if (score > maxScore) {
            maxScore = score;
            bestLabelIndex = labelIndex;
        }
    }
    return labelStringList[bestLabelIndex];
}

}  // namespace MaxEnt
#endif  // HOCRF_MAX_ENT_OBSERVATION_H_
