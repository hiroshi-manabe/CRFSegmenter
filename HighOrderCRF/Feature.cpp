#include "Feature.h"
#include "FeatureTemplate.h"
#include "LabelSequence.h"

#include <algorithm>
#include <cmath>
#include <memory>
#include <string>

namespace HighOrderCRF {

using std::make_shared;
using std::shared_ptr;
using std::string;

Feature::Feature(string obs, const shared_ptr<LabelSequence> pat) {
    this->obs = obs;
    this->pat = pat;
}

Feature::Feature(string obs, const shared_ptr<LabelSequence> pat, feature_index_t index) {
    this->obs = obs;
    this->pat = pat;
    this->index = index;
}

void Feature::setIndex(feature_index_t index) {
    this->index = index;
}

feature_index_t Feature::getIndex() const {
    return index;
}

shared_ptr<LabelSequence> Feature::getLabelSequence() const {
    return pat;
}

const string &Feature::getObservation() const {
    return obs;
}

shared_ptr<FeatureTemplate> Feature::createFeatureTemplate() const {
    return make_shared<FeatureTemplate>(obs, pat->getLength());
}

bool Feature::operator==(const Feature &that) const {
    return this->getObservation() == that.getObservation() && *this->getLabelSequence() == *that.getLabelSequence();
}

size_t Feature::hash() const
{
    return std::hash<string>()(obs) ^ pat->hash();
};

}  // namespace HighOrderCRF

