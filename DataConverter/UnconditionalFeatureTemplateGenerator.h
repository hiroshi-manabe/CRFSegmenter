#ifndef HOCRF_DATA_CONVERTER_UNCONDITIONAL_FEATURE_TEMPLATE_GENERATOR_H_
#define HOCRF_DATA_CONVERTER_UNCONDITIONAL_FEATURE_TEMPLATE_GENERATOR_H_

#include "FeatureTemplateGenerator.h"

#include <algorithm>
#include <memory>
#include <vector>

namespace DataConverter {

template <typename T>
class UnconditionalFeatureTemplateGenerator : public FeatureTemplateGenerator<T>
{
public:
    UnconditionalFeatureTemplateGenerator(size_t maxLabelLength) : maxLabelLength(maxLabelLength) {};
    virtual std::vector<std::vector<HighOrderCRF::FeatureTemplate>> generateFeatureTemplates(const std::vector<T> &observationList) const {
        std::vector<std::vector<HighOrderCRF::FeatureTemplate>> featureTemplateListList(observationList.size());
        for (size_t pos = 0; pos < observationList.size(); ++pos) {
            for (size_t i = 1; i <= std::min(maxLabelLength, pos + 1); ++i) {
                featureTemplateListList[pos].emplace_back("*", i);
            }
        }
        return featureTemplateListList;
    }
private:
    size_t maxLabelLength;
};

}  // namespace DataConverter

#endif  // HOCRF_DATA_CONVERTER_UNCONDITIONAL_FEATURE_TEMPLATE_GENERATOR_H
