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

Feature::Feature(string tag, shared_ptr<LabelSequence> seq) {
    this->tag = move(tag);
    this->seq = seq;
}

shared_ptr<LabelSequence> Feature::getLabelSequence() const {
    return seq;
}

const string &Feature::getTag() const {
    return tag;
}

bool Feature::operator==(const Feature &that) const {
    return this->getTag() == that.getTag() && *this->getLabelSequence() == *that.getLabelSequence();
}

size_t Feature::hash() const
{
    return std::hash<string>()(tag) ^ seq->hash();
};

}  // namespace HighOrderCRF

