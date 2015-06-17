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
struct hash<HighOrderCRF::Feature> {
    std::size_t operator()(const HighOrderCRF::Feature &feature) const {
        return feature.hash();
    }
};

}  // namespace std

#endif  // HOCRF_HIGH_ORDER_CRF_FEATURE_H
