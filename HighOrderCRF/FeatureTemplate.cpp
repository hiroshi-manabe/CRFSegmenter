#include "FeatureTemplate.h"

#include "Feature.h"
#include "LabelSequence.h"

#include <memory>
#include <string>

namespace HighOrderCRF {

using std::make_shared;
using std::shared_ptr;
using std::string;

FeatureTemplate::FeatureTemplate(const string tag, size_t labelLength) {
    this->tag = tag;
    this->labelLength = labelLength;
}

size_t FeatureTemplate::getLabelLength() const {
    return labelLength;
}

const string &FeatureTemplate::getTag() const {
    return tag;
}

bool FeatureTemplate::operator==(const FeatureTemplate &that) const {
    return this->getLabelLength() == that.getLabelLength() && this->tag == that.tag;
}

size_t FeatureTemplate::hash() const {
    return std::hash<string>()(tag) ^ std::hash<size_t>()(labelLength);
}

}  // namespace HighOrderCRF

