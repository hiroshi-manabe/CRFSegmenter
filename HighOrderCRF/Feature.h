#ifndef HOCRF_HIGH_ORDER_CRF_FEATURE_H_
#define HOCRF_HIGH_ORDER_CRF_FEATURE_H_

#include "types.h"

#include "LabelSequence.h"

#include <string>

namespace HighOrderCRF {

class FeatureTemplate;

class Feature
{
public:
    Feature(std::string tag, LabelSequence seq);
    const LabelSequence &getLabelSequence() const;
    const std::string &getTag() const;
    bool operator==(const Feature &that) const;
    size_t hash() const;

private:
    std::string tag;
    LabelSequence seq;
};

}  // namespace HighOrderCRF

namespace std {

template<> 
struct hash<HighOrderCRF::Feature> {
    size_t operator()(const HighOrderCRF::Feature &feature) const {
        return feature.hash();
    }
};

}  // namespace std

#endif  // HOCRF_HIGH_ORDER_CRF_FEATURE_H
