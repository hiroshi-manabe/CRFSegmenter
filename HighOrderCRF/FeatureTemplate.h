#ifndef HOCRF_FEATURE_TEMPLATE_H_
#define HOCRF_FEATURE_TEMPLATE_H_

#include "types.h"

#include <memory>
#include <string>

namespace HighOrderCRF {

using std::shared_ptr;
using std::string;

class LabelSequence;
class Feature;

class FeatureTemplate
{
public:
    FeatureTemplate(const string obs, size_t order);
    const shared_ptr<Feature> generateFeature(const shared_ptr<LabelSequence> seq) const;
    size_t getLabelLength() const;
    const string &getObservation() const;
    bool operator==(const FeatureTemplate &that);
    size_t hash() const;

private:
    string obs;
    size_t labelLength;
};

}  // namespace HighOrderCRF
#endif  // HOCRF_FEATURE_TEMPLATE_H
