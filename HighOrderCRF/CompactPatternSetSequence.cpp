#include "CompactPatternSetSequence.h"

#include "CompactPattern.h"
#include "Feature.h"

#include <algorithm>
#include <mutex>
#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::copy;
using std::fill;
using std::make_shared;
using std::mutex;
using std::shared_ptr;
using std::swap;
using std::vector;

shared_ptr<vector<vector<double>>> getAccumulatedWeightListList(shared_ptr<vector<vector<CompactPattern>>> compactPatternListList, const double *expWeights) {
    auto ret = make_shared<vector<vector<double>>>(0);
    
    // accumulates weights
    for (size_t pos = 0; pos < compactPatternListList->size(); ++pos) {
        auto &curPatternList = (*compactPatternListList)[pos];
        ret->push_back(vector<double>(curPatternList.size()));
        auto &curWeightList = ret->back();
        curWeightList[0] = 1.0;
        
        for (size_t i = 1; i < curPatternList.size(); ++i) {
            auto &curPattern = curPatternList[i];
            auto &curWeight = curWeightList[i];
            curWeight = 1.0;
            for (auto &featureIndex : *curPattern.getFeatureIndexList()) {
                curWeight *= expWeights[featureIndex];
            }
            curWeight *= curWeightList[curPattern.getLongestSuffixIndex()];
        }
    }
    return ret;
}

void CompactPatternSetSequence::accumulateFeatureCounts(double *counts) const {
    for (size_t pos = 0; pos < compactPatternListList->size(); ++pos) {
        auto &compactPatternList = (*compactPatternListList)[pos];
        pattern_index_t index = (*longestMatchIndexList)[pos];
        while (index != 0) {
            for (auto featureIndex : *compactPatternList[index].getFeatureIndexList()) {
                counts[featureIndex] += 1.0;
            }
            index = compactPatternList[index].getLongestSuffixIndex();
        }
    }
}

static mutex expectationMutex;
// returns log likelihood of the sequence
double CompactPatternSetSequence::accumulateFeatureExpectations(const double *expWeights, double *expectations) const {
    size_t maxPatternSetSize = 0;
    size_t sequenceLength = compactPatternListList->size();
    vector<vector<double>> scoreListList(0);
    vector<int> exponents(sequenceLength);

    for (auto &compactPatternList : *compactPatternListList) {
        size_t size = compactPatternList.size();
        if (size > maxPatternSetSize) {
            maxPatternSetSize = size;
        }
        scoreListList.push_back(vector<double>(size));
    }

    vector<double> tempScoreList1(maxPatternSetSize);
    vector<double> tempScoreList2(maxPatternSetSize);

    vector<double> *curTempScoreList = &tempScoreList1;
    vector<double> *prevTempScoreList = &tempScoreList2;

    auto weightListList = getAccumulatedWeightListList(compactPatternListList, expWeights);

    // forward calculations

    int exponentDiff = 0;
    (*prevTempScoreList)[0] = 1.0;  // gamma for the position -1
    exponents[0] = 0;

    for (size_t pos = 0; pos < sequenceLength; ++pos) {
        auto &curPatternList = (*compactPatternListList)[pos];
        auto &scoreList = scoreListList[pos];
        auto &weightList = (*weightListList)[pos];
        size_t listSize = curPatternList.size();
        
        fill(curTempScoreList->begin(), curTempScoreList->begin() + listSize, 0.0);
        double scale = ldexp(1.0, -exponentDiff);
        
        for (size_t index = listSize - 1; index > 0; --index) {
            auto &curPattern = curPatternList[index];
            auto longestSuffixIndex = curPattern.getLongestSuffixIndex();
            auto prevPatternIndex = curPattern.getPrevPatternIndex();

            double prevGamma = (*prevTempScoreList)[prevPatternIndex] * scale;

            // calculates alphas
            scoreList[longestSuffixIndex] -= prevGamma;
            scoreList[index] += prevGamma;

            // calculates gammas
            (*curTempScoreList)[index] += scoreList[index] * weightList[index];
            (*curTempScoreList)[longestSuffixIndex] += (*curTempScoreList)[index];
        }
        scoreList[0] = 0.0;  // alpha for an empty pattern is 0
        frexp((*curTempScoreList)[0], &exponentDiff);  // gets the exponent of the gamma of the empty pattern

        if (pos < sequenceLength - 1) {
            exponents[pos + 1] = exponents[pos] + exponentDiff;
        }
        swap(curTempScoreList, prevTempScoreList);
    }
    
    double normalizer = (*prevTempScoreList)[0];
    int normalizerExponent = exponents[sequenceLength - 1];

    // backward calculations

    size_t lastListLength = (*compactPatternListList)[sequenceLength - 1].size();
    // clears deltas
    fill(curTempScoreList->begin(), curTempScoreList->begin() + lastListLength, 0.0);
    // delta for the empty pattern
    (*curTempScoreList)[0] = 1;

    for (size_t pos = sequenceLength; pos-- > 0; ) {
        auto &curPatternList = (*compactPatternListList)[pos];
        auto &scoreList = scoreListList[pos];
        auto &weightList = (*weightListList)[pos];
        size_t listSize = curPatternList.size();
        size_t prevListSize = (pos > 0) ? (*compactPatternListList)[pos - 1].size() : 1;

        fill(prevTempScoreList->begin(), prevTempScoreList->begin() + prevListSize, 0.0);
        double scale = ldexp(1.0, (pos > 0) ? (exponents[pos - 1] - exponents[pos]) : 0);

        for (size_t index = 1; index < listSize; ++index) {
            auto longestSuffixIndex = curPatternList[index].getLongestSuffixIndex();
            // beta
            (*curTempScoreList)[index] += (*curTempScoreList)[longestSuffixIndex];
        }

        (*curTempScoreList)[0] = 0;
        for (size_t index = 1; index < listSize; ++index) {
            auto &curPattern = curPatternList[index];
            auto longestSuffixIndex = curPattern.getLongestSuffixIndex();
            auto prevPatternIndex = curPattern.getPrevPatternIndex();

            // beta * W
            (*curTempScoreList)[index] *= weightList[index];
            
            // theta (alpha * beta * W)
            scoreList[index] *= (*curTempScoreList)[index];

            // delta
            (*prevTempScoreList)[prevPatternIndex] += ((*curTempScoreList)[index] - (*curTempScoreList)[longestSuffixIndex]) * scale;
        }

        // sigma
        for (size_t index = listSize - 1; index > 0; --index) {
            auto longestSuffixIndex = curPatternList[index].getLongestSuffixIndex();
            scoreList[longestSuffixIndex] += scoreList[index];
        }

        // normalizes the scores and accumulates feature expectations
        for (size_t index = listSize - 1; index > 0; --index) {
            scoreList[index] /= scoreList[0];
        }
        
        swap(prevTempScoreList, curTempScoreList);
    }
    
    // accumulates expectations
    expectationMutex.lock();
    for (size_t pos = 0; pos < sequenceLength; ++pos) {
#ifdef EMULATE_BOS_EOS
        if (pos == 0 || pos == sequenceLength - 1) {
            continue;
        }
#endif
        auto &curPatternList = (*compactPatternListList)[pos];
        for (size_t index = 1; index < curPatternList.size(); ++index) {
            for (auto &featureIndex : *curPatternList[index].getFeatureIndexList()) {
                expectations[featureIndex] += scoreListList[pos][index];
            }
        }
    }
    expectationMutex.unlock();

    // calculates the log likelihood of the sequence
    double logLikelihood = -(log(normalizer) + log(2.0) * normalizerExponent);
    for (size_t pos = 0; pos < sequenceLength; ++pos) {
        auto &weightList = (*weightListList)[pos];
        logLikelihood += log(weightList[(*longestMatchIndexList)[pos]]);
    }
    
    return logLikelihood;
}

shared_ptr<vector<label_t>> CompactPatternSetSequence::decode(const double *expWeights) const {
    size_t maxPatternSetSize = 0;
    size_t sequenceLength = compactPatternListList->size();

    vector<vector<pattern_index_t>> bestIndexListList(0);
    bestIndexListList.reserve(sequenceLength);

    for (auto &compactPatternList : *compactPatternListList) {
        size_t size = compactPatternList.size();
        if (size > maxPatternSetSize) {
            maxPatternSetSize = size;
        }
        bestIndexListList.push_back(vector<pattern_index_t>(size));
    }

    vector<pattern_index_t> bestPrefixIndexList(maxPatternSetSize);
    vector<double> tempScoreList1(maxPatternSetSize);
    vector<double> tempScoreList2(maxPatternSetSize);

    vector<double> *curTempScoreList = &tempScoreList1;
    vector<double> *prevTempScoreList = &tempScoreList2;
    vector<double> prevTempScoreListForLabel(maxPatternSetSize);

    auto weightListList = getAccumulatedWeightListList(compactPatternListList, expWeights);
    int exponentDiff = 0;
    double scale = 1.0;

    (*prevTempScoreList)[0] = 1.0;

    for (size_t pos = 0; pos < sequenceLength; ++pos) {
        auto &curPatternList = (*compactPatternListList)[pos];
        auto &bestIndexList = bestIndexListList[pos];
        auto &weightList = (*weightListList)[pos];
        size_t listSize = curPatternList.size();
        size_t prevListSize = (pos > 0) ? (*compactPatternListList)[pos - 1].size() : 1;
        
        fill(curTempScoreList->begin(), curTempScoreList->begin() + listSize, 0);

        label_t prevLabel = INVALID_LABEL;
        size_t prevIndex = prevListSize;
        double maxScore = 0.0;

        for (size_t index = listSize - 1; index > 0; --index) {
            auto &curPattern = curPatternList[index];
            if (curPattern.getLastLabel() != prevLabel) {
                copy(prevTempScoreList->begin(), prevTempScoreList->begin() + prevListSize, prevTempScoreListForLabel.begin());
                for (size_t i = 0; i < prevListSize; ++i) {
                    bestPrefixIndexList[i] = i;
                }
                prevIndex = prevListSize;
            }
            prevLabel = curPattern.getLastLabel();
            --prevIndex;
            for (; prevIndex > curPattern.getPrevPatternIndex(); --prevIndex) {
                auto longestSuffixIndex = (*compactPatternListList)[pos - 1][prevIndex].getLongestSuffixIndex();
                if (prevTempScoreListForLabel[prevIndex] > prevTempScoreListForLabel[longestSuffixIndex]) {
                    prevTempScoreListForLabel[longestSuffixIndex] = prevTempScoreListForLabel[prevIndex];
                    bestPrefixIndexList[longestSuffixIndex] = bestPrefixIndexList[prevIndex];
                }
            }
            (*curTempScoreList)[index] = prevTempScoreListForLabel[prevIndex] * weightList[index];
            bestIndexList[index] = bestPrefixIndexList[prevIndex];
            if ((*curTempScoreList)[index] > maxScore) {
                maxScore = (*curTempScoreList)[index];
            }
        }
        frexp(maxScore, &exponentDiff);
        scale = ldexp(1.0, -exponentDiff);
        for (size_t index = 1; index < listSize; ++index) {
            (*curTempScoreList)[index] *= scale;
        }
        swap(curTempScoreList, prevTempScoreList);
    }

    double lastBestScore = 0.0;
    size_t bestIndex = 0;

    for (size_t index = 1; index < compactPatternListList->back().size(); ++index) {
        if ((*prevTempScoreList)[index] > lastBestScore) {
            lastBestScore = (*prevTempScoreList)[index];
            bestIndex = index;
        }
    }

    auto bestLabelList = make_shared<vector<label_t>>(sequenceLength);
    for (size_t pos = sequenceLength; pos-- > 0;) {
        auto &curPatternList = (*compactPatternListList)[pos];
        auto &bestIndexList = bestIndexListList[pos];
        
        (*bestLabelList)[pos] = curPatternList[bestIndex].getLastLabel();
        bestIndex = bestIndexList[bestIndex];
    }

    return bestLabelList;
}

}  // namespace HighOrderCRF
