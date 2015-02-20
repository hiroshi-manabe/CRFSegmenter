#include "PatternSetSequence.h"

#include "CompactPattern.h"
#include "CompactPatternSetSequence.h"
#include "Feature.h"
#include "Pattern.h"

#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::make_shared;
using std::move;
using std::shared_ptr;
using std::vector;

shared_ptr<CompactPatternSetSequence> PatternSetSequence::generateCompactPatternSetSequence() {
    auto compactPatternListList = make_shared<vector<vector<CompactPattern>>>();
    auto longestMatchIndexList = make_shared<vector<pattern_index_t>>();
    
    for (size_t pos = 0; pos < patternListList->size(); ++pos) {
        auto &patternList = patternListList->at(pos);
        auto &curFirstPattern = patternList->at(0);
        auto prevFirstPattern = (pos > 0 ? patternListList->at(pos - 1)->at(0) : Pattern::getDummyPattern());

        vector<CompactPattern> compactPatternList(0);
        compactPatternList.reserve(patternList->size());
        for (pattern_index_t index = 0; index < patternList->size(); ++index) {
            auto &curPattern = patternList->at(index);
            curPattern->setIndex(index);
            pattern_index_t prevPatternIndex;
            pattern_index_t longestSuffixPatternIndex;

            if (pos == 0) {
                prevPatternIndex = 0;
            } else {
                prevPatternIndex = curPattern->getPrevPattern()->getIndex();
            }
            longestSuffixPatternIndex = curPattern->getLongestSuffixPattern()->getIndex();
            auto featureIndexList = make_shared<vector<feature_index_t>>();
            for (auto &feature : *curPattern->getFeatureList()) {
                featureIndexList->push_back(feature->getIndex());
            }
            compactPatternList.push_back(CompactPattern(prevPatternIndex, longestSuffixPatternIndex, curPattern->getLastLabel(), featureIndexList));
        }
        compactPatternListList->push_back(move(compactPatternList));
        longestMatchIndexList->push_back(longestMatchPatternList->at(pos)->getIndex());
    }
    return make_shared<CompactPatternSetSequence>(compactPatternListList, longestMatchIndexList);
}

}  // namespace HighOrderCRF
