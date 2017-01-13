#ifndef HOCRF_DATA_CONVERTER_HIGH_ORDER_CRF_AGGREGATED_FEATURE_TEMPLATE_GENERATOR_H_
#define HOCRF_DATA_CONVERTER_HIGH_ORDER_CRF_AGGREGATED_FEATURE_TEMPLATE_GENERATOR_H_

#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

#include "FeatureTemplateGenerator.h"

namespace DataConverter {

template <typename T>
class AggregatedFeatureTemplateGenerator : public FeatureTemplateGenerator<T>
{
public:
    AggregatedFeatureTemplateGenerator<T>() {};
    
    virtual std::vector<std::vector<HighOrderCRF::FeatureTemplate>> generateFeatureTemplates(const std::vector<T> &observationList) const {
        std::vector<std::vector<HighOrderCRF::FeatureTemplate>> templateListList(observationList.size());
        for (auto &generator : generatorList) {
            auto generatedListList = generator->generateFeatureTemplates(observationList);
            for (size_t i = 0; i < observationList.size(); ++i) {
                std::move(generatedListList[i].begin(), generatedListList[i].end(), std::back_inserter(templateListList[i]));
            }
        }
        return templateListList;
    }

    void addFeatureTemplateGenerator(std::shared_ptr<FeatureTemplateGenerator<T>> generator) {
        generatorList.emplace_back(generator);
    }
private:
    std::vector<std::shared_ptr<FeatureTemplateGenerator<T>>> generatorList;
};

}  // namespace DataConverter

#endif  // HOCRF_DATA_CONVERTER_HIGH_ORDER_CRF_AGGREGATED_FEATURE_TEMPLATE_GENERATOR_H
