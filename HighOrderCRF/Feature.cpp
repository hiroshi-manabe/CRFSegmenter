#include <algorithm>
#include <cmath>
#include <string>
#include <utility>

#include "Feature.h"
#include "FeatureTemplate.h"
#include "LabelSequence.h"

namespace HighOrderCRF {

using std::move;
using std::string;

Feature::Feature(string tag, LabelSequence seq) {
    this->tag = move(tag);
    this->seq = move(seq);
}

const LabelSequence &Feature::getLabelSequence() const {
    return seq;
}

const string &Feature::getTag() const {
    return tag;
}

bool Feature::operator==(const Feature &that) const {
    return this->getTag() == that.getTag() && this->getLabelSequence() == that.getLabelSequence();
}

size_t Feature::hash() const
{
    return std::hash<string>()(tag) ^ seq.hash();
};

}  // namespace HighOrderCRF

