#ifndef HOCRF_AGGREGATED_FEATURE_TEMPLATE_GENERATOR_H_
#define HOCRF_AGGREGATED_FEATURE_TEMPLATE_GENERATOR_H_

#include "types.h"

#include "FeatureTemplateGenerator.h"

#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::make_shared;
using std::shared_ptr;
using std::vector;

class FeatureTemplate;

template <typename T>
class AggregatedFeatureTemplateGenerator : public FeatureTemplateGenerator<T>
{
public:
    AggregatedFeatureTemplateGenerator<T>() {
        generatorList = make_shared<vector<shared_ptr<FeatureTemplateGenerator<T>>>>();
    }
    
    virtual shared_ptr<vector<shared_ptr<FeatureTemplate>>> generateFeatureTemplatesAt(shared_ptr<vector<T>> observationList, size_t pos) const {
        auto templateList = make_shared<vector<shared_ptr<FeatureTemplate>>>();
        for (auto &generator : *generatorList) {
            auto generatedList = generator->generateFeatureTemplatesAt(observationList, pos);
            templateList->insert(templateList->end(), generatedList->begin(), generatedList->end());
        }
        return templateList;
    }

    void addFeatureTemplateGenerator(shared_ptr<FeatureTemplateGenerator<T>> generator) {
        generatorList->push_back(generator);
    }
private:
    shared_ptr<vector<shared_ptr<FeatureTemplateGenerator<T>>>> generatorList;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_AGGREGATED_FEATURE_TEMPLATE_GENERATOR_H
