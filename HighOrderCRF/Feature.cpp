#include "Feature.h"
#include "FeatureTemplate.h"
#include "LabelSequence.h"

#include <algorithm>
#include <cmath>
#include <memory>
#include <string>
#include <utility>

namespace HighOrderCRF {

using std::make_shared;
using std::move;
using std::shared_ptr;
using std::string;

Feature::Feature(string obs, LabelSequence pat) {
    this->obs = move(obs);
    this->pat = pat;
}

LabelSequence Feature::getLabelSequence() const {
    return pat;
}

const string &Feature::getObservation() const {
    return obs;
}

shared_ptr<FeatureTemplate> Feature::createFeatureTemplate() const {
    return make_shared<FeatureTemplate>(obs, pat.getLength());
}

bool Feature::operator==(const Feature &that) const {
    return this->getObservation() == that.getObservation() && this->getLabelSequence() == that.getLabelSequence();
}

size_t Feature::hash() const
{
    return std::hash<string>()(obs) ^ pat.hash();
};

}  // namespace HighOrderCRF

