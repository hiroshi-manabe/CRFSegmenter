#include "FeatureTemplate.h"

#include "Feature.h"
#include "LabelSequence.h"

#include <memory>
#include <string>

namespace HighOrderCRF {

using std::make_shared;
using std::shared_ptr;
using std::string;

FeatureTemplate::FeatureTemplate(const string obs, size_t labelLength) {
    this->obs = obs;
    this->labelLength = labelLength;
}

size_t FeatureTemplate::getLabelLength() const {
    return labelLength;
}

const string &FeatureTemplate::getObservation() const {
    return obs;
}

bool FeatureTemplate::operator==(const FeatureTemplate &that) const {
    return this->getLabelLength() == that.getLabelLength() && this->obs == that.obs;
}

size_t FeatureTemplate::hash() const {
    return std::hash<string>()(obs) ^ std::hash<size_t>()(labelLength);
}

}  // namespace HighOrderCRF

