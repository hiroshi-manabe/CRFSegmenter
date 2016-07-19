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
    FeatureTemplate(const string tag, size_t labelLength);
    size_t getLabelLength() const;
    const string &getTag() const;
    bool operator==(const FeatureTemplate &that) const;
    size_t hash() const;

private:
    string tag;
    size_t labelLength;
};

}  // namespace HighOrderCRF

namespace std {

template<>
struct hash<shared_ptr<HighOrderCRF::FeatureTemplate>> {
    size_t operator()(const shared_ptr<HighOrderCRF::FeatureTemplate> &featureTemplate) const {
        return featureTemplate->hash();
    }
};

template<>
struct equal_to<shared_ptr<HighOrderCRF::FeatureTemplate>> {
    bool operator()(const shared_ptr<HighOrderCRF::FeatureTemplate>& left, const shared_ptr<HighOrderCRF::FeatureTemplate> &right) const {
        return *left == *right;
    }
};

}  // namespace std

#endif  // HOCRF_HIGH_ORDER_CRF_FEATURE_TEMPLATE_H
