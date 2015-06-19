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

Feature::Feature(string obs, shared_ptr<LabelSequence> seq) {
    this->obs = move(obs);
    this->seq = seq;
}

shared_ptr<LabelSequence> Feature::getLabelSequence() const {
    return seq;
}

const string &Feature::getObservation() const {
    return obs;
}

bool Feature::operator==(const Feature &that) const {
    return this->getObservation() == that.getObservation() && *this->getLabelSequence() == *that.getLabelSequence();
}

size_t Feature::hash() const
{
    return std::hash<string>()(obs) ^ seq->hash();
};

}  // namespace HighOrderCRF

