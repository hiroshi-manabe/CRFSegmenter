#ifndef HOCRF_HIGH_ORDER_CRF_FEATURE_H_
#define HOCRF_HIGH_ORDER_CRF_FEATURE_H_

#include "types.h"

#include "LabelSequence.h"

#include <memory>
#include <string>

namespace HighOrderCRF {

class FeatureTemplate;

using std::shared_ptr;
using std::string;

class Feature
{
public:
    Feature(string obs, LabelSequence pat);
    LabelSequence getLabelSequence() const;
    const string &getObservation() const;
    shared_ptr<FeatureTemplate> createFeatureTemplate() const;
    bool operator==(const Feature &that) const;
    size_t hash() const;

private:
    string obs;
    LabelSequence pat;
};

}  // namespace HighOrderCRF

namespace std {

template<> 
struct hash<shared_ptr<HighOrderCRF::Feature>> {
    std::size_t operator()(const shared_ptr<HighOrderCRF::Feature> &feature) const {
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
