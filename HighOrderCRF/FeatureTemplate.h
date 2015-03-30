#ifndef HOCRF_HIGH_ORDER_CRF_FEATURE_TEMPLATE_H_
#define HOCRF_HIGH_ORDER_CRF_FEATURE_TEMPLATE_H_

#include "types.h"

#include "Feature.h"
#include "LabelSequence.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace HighOrderCRF {

using std::shared_ptr;
using std::string;

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



namespace std {

    template<>
    struct hash<std::shared_ptr<HighOrderCRF::FeatureTemplate>> {
        std::size_t operator()(const std::shared_ptr<HighOrderCRF::FeatureTemplate> &featureTemplate) const {
            return featureTemplate->hash();
        }
    };

    template<>
    struct equal_to<std::shared_ptr<HighOrderCRF::FeatureTemplate>> {
        bool operator()(const std::shared_ptr<HighOrderCRF::FeatureTemplate>& left, const std::shared_ptr<HighOrderCRF::FeatureTemplate> &right) const {
            return *left == *right;
        }
    };

}

#endif  // HOCRF_HIGH_ORDER_CRF_FEATURE_TEMPLATE_H
