#include "Pattern.h"

#include "Feature.h"

#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::make_shared;
using std::shared_ptr;
using std::vector;

shared_ptr<Pattern> Pattern::DUMMY_PATTERN = make_shared<Pattern>(INVALID_LABEL);

Pattern::Pattern(label_t lastLabel) {
    prevPattern = DUMMY_PATTERN;
    longestSuffixPattern = DUMMY_PATTERN;
    featureList = make_shared<vector<shared_ptr<Feature>>>();
    this->lastLabel = lastLabel;
    this->index = 0;
}

void Pattern::setPrevPattern(shared_ptr<Pattern> pattern) {
    prevPattern = pattern;
}

shared_ptr<Pattern> Pattern::getPrevPattern() const {
    return prevPattern;
}

void Pattern::setLongestSuffixPattern(shared_ptr<Pattern> pattern) {
    longestSuffixPattern = pattern;
}

shared_ptr<Pattern> Pattern::getLongestSuffixPattern() const {
    return longestSuffixPattern;
}

void Pattern::addFeature(shared_ptr<Feature> feature) {
    featureList->push_back(feature);
}

shared_ptr<vector<shared_ptr<Feature>>> Pattern::getFeatureList() const {
    return featureList;
}

label_t Pattern::getLastLabel() const {
    return lastLabel;
}

void Pattern::setIndex(pattern_index_t index) {
    this->index = index;
}

pattern_index_t Pattern::getIndex() const {
    return this->index;
}

shared_ptr<Pattern> Pattern::getDummyPattern() {
    return DUMMY_PATTERN;
}

}  // namespace HighOrderCRF
