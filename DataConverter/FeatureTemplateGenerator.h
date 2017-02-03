#ifndef HOCRF_DATA_CONVERTER_FEATURE_TEMPLATE_GENERATOR_H_
#define HOCRF_DATA_CONVERTER_FEATURE_TEMPLATE_GENERATOR_H_

#include <memory>
#include <vector>

#include "../HighOrderCRF/FeatureTemplate.h"

namespace DataConverter {

template <typename T>
class FeatureTemplateGenerator
{
public:
    virtual std::vector<std::vector<HighOrderCRF::FeatureTemplate>> generateFeatureTemplates(const std::vector<T> &observationList) const = 0;
};

}  // namespace DataConverter

#endif  // HOCRF_DATA_CONVERTER_FEATURE_TEMPLATE_GENERATOR_H
