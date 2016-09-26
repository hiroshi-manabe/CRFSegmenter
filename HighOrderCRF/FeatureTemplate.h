#ifndef HOCRF_HIGH_ORDER_CRF_FEATURE_TEMPLATE_H_
#define HOCRF_HIGH_ORDER_CRF_FEATURE_TEMPLATE_H_

#include <memory>
#include <string>

namespace HighOrderCRF {

class FeatureTemplate
{
public:
    FeatureTemplate(const std::string tag, size_t labelLength) {
        this->tag = tag;
        this->labelLength = labelLength;
    }

    size_t getLabelLength() const {
        return labelLength;
    }
        
    const std::string &getTag() const {
        return tag;
    }
    
    bool operator==(const FeatureTemplate &that) const {
        return this->getLabelLength() == that.getLabelLength() && this->tag == that.tag;
    }
    
    size_t hash() const {
        return std::hash<std::string>()(tag) ^ std::hash<size_t>()(labelLength);
    }

private:
    std::string tag;
    size_t labelLength;
};

}  // namespace HighOrderCRF

namespace std {

template<>
struct hash<std::shared_ptr<HighOrderCRF::FeatureTemplate>> {
    size_t operator()(const std::shared_ptr<HighOrderCRF::FeatureTemplate> &featureTemplate) const {
        return featureTemplate->hash();
    }
};

template<>
struct equal_to<std::shared_ptr<HighOrderCRF::FeatureTemplate>> {
    bool operator()(const std::shared_ptr<HighOrderCRF::FeatureTemplate>& left, const std::shared_ptr<HighOrderCRF::FeatureTemplate> &right) const {
        return *left == *right;
    }
};

}  // namespace std

#endif  // HOCRF_HIGH_ORDER_CRF_FEATURE_TEMPLATE_H
