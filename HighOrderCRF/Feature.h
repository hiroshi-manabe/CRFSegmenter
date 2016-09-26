#ifndef HOCRF_HIGH_ORDER_CRF_FEATURE_H_
#define HOCRF_HIGH_ORDER_CRF_FEATURE_H_

#include "types.h"

#include "LabelSequence.h"

#include <memory>
#include <string>

namespace HighOrderCRF {

class FeatureTemplate;

class Feature
{
public:
    Feature(std::string tag, std::shared_ptr<LabelSequence> pat);
    std::shared_ptr<LabelSequence> getLabelSequence() const;
    const std::string &getTag() const;
    bool operator==(const Feature &that) const;
    size_t hash() const;

private:
    std::string tag;
    std::shared_ptr<LabelSequence> seq;
};

}  // namespace HighOrderCRF

namespace std {

template<> 
struct hash<std::shared_ptr<HighOrderCRF::Feature>> {
    size_t operator()(const std::shared_ptr<HighOrderCRF::Feature> &feature) const {
        return feature->hash();
    }
};

template<>
struct equal_to<std::shared_ptr<HighOrderCRF::Feature>> {
    bool operator()(const std::shared_ptr<HighOrderCRF::Feature>& left, const std::shared_ptr<HighOrderCRF::Feature> &right) const {
        return *left == *right;
    }
};

}  // namespace std

#endif  // HOCRF_HIGH_ORDER_CRF_FEATURE_H
