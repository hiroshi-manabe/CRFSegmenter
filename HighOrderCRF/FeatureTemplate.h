#ifndef HOCRF_HIGH_ORDER_CRF_FEATURE_TEMPLATE_H_
#define HOCRF_HIGH_ORDER_CRF_FEATURE_TEMPLATE_H_

#include <memory>
#include <string>

namespace HighOrderCRF {

class FeatureTemplate {
public:
    FeatureTemplate(const std::string &tag, size_t labelLength);
    FeatureTemplate(const std::string &str);
    size_t getLabelLength() const;
    const std::string &getTag() const;
    std::string toString() const;
    bool operator==(const FeatureTemplate &that) const;
    size_t hash() const;

private:
    std::string tag;
    size_t labelLength;
};

}  // namespace HighOrderCRF

namespace std {

template<>
struct hash<HighOrderCRF::FeatureTemplate> {
    size_t operator()(const HighOrderCRF::FeatureTemplate &featureTemplate) const {
        return featureTemplate.hash();
    }
};

}  // namespace std

#endif  // HOCRF_HIGH_ORDER_CRF_FEATURE_TEMPLATE_H
