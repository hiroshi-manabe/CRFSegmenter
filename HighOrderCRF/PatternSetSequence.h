#ifndef HOCRF_HIGH_ORDER_CRF_PATTERN_SET_SEQUENCE_H_
#define HOCRF_HIGH_ORDER_CRF_PATTERN_SET_SEQUENCE_H_

#include "types.h"

#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::shared_ptr;
using std::vector;

class CompactPatternSetSequence;
class Pattern;

class PatternSetSequence
{
public:
    PatternSetSequence(shared_ptr<vector<shared_ptr<vector<shared_ptr<Pattern>>>>> patternListList,
        shared_ptr<vector<shared_ptr<Pattern>>> longestMatchPatternList) :
        patternListList(patternListList), longestMatchPatternList(longestMatchPatternList) {};
    shared_ptr<CompactPatternSetSequence> generateCompactPatternSetSequence();

private:
    shared_ptr<vector<shared_ptr<vector<shared_ptr<Pattern>>>>> patternListList;
    shared_ptr<vector<shared_ptr<Pattern>>> longestMatchPatternList;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_HIGH_ORDER_CRF_PATTERN_SET_SEQUENCE_H
