#ifndef HOCRF_HIGH_ORDER_CRF_PATTERN_H_
#define HOCRF_HIGH_ORDER_CRF_PATTERN_H_

#include "types.h"
#include "Feature.h"

#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::shared_ptr;
using std::vector;

class Pattern
{
public:
    Pattern(label_t lastLabel);
    void setPrevPattern(shared_ptr<Pattern> pattern);
    shared_ptr<Pattern> getPrevPattern() const;
    void setLongestSuffixPattern(shared_ptr<Pattern> pattern);
    shared_ptr<Pattern> getLongestSuffixPattern() const;
    void addFeature(shared_ptr<Feature> feature);
    shared_ptr<vector<shared_ptr<Feature>>> getFeatureList() const;
    label_t getLastLabel() const;
    void setIndex(pattern_index_t);
    pattern_index_t getIndex() const;

    static shared_ptr<Pattern> getDummyPattern();

private:
    shared_ptr<Pattern> prevPattern;
    shared_ptr<Pattern> longestSuffixPattern;
    shared_ptr<vector<shared_ptr<Feature>>> featureList;
    label_t lastLabel;
    pattern_index_t index;

    static shared_ptr<Pattern> DUMMY_PATTERN;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_HIGH_ORDER_CRF_PATTERN_H
