#ifndef HOCRF_HIGH_ORDER_CRF_AGGREGATED_FEATURE_TEMPLATE_GENERATOR_H_
#define HOCRF_HIGH_ORDER_CRF_AGGREGATED_FEATURE_TEMPLATE_GENERATOR_H_

#include "types.h"

#include "FeatureTemplate.h"
#include "FeatureTemplateGenerator.h"

#include <algorithm>
#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::back_inserter;
using std::make_shared;
using std::move;
using std::shared_ptr;
using std::vector;

template <typename T>
class AggregatedFeatureTemplateGenerator : public FeatureTemplateGenerator<T>
{
public:
    AggregatedFeatureTemplateGenerator<T>() {
        generatorList = make_shared<vector<shared_ptr<FeatureTemplateGenerator<T>>>>();
    }
    
    virtual shared_ptr<vector<vector<shared_ptr<FeatureTemplate>>>> generateFeatureTemplates(shared_ptr<vector<T>> observationList) const {
        auto templateListList = make_shared<vector<vector<shared_ptr<FeatureTemplate>>>>(observationList->size());
        for (auto &generator : *generatorList) {
            auto generatedListList = generator->generateFeatureTemplates(observationList);
            for (size_t i = 0; i < observationList->size(); ++i) {
                move((*generatedListList)[i].begin(), (*generatedListList)[i].end(), back_inserter((*templateListList)[i]));
            }
        }
        return templateListList;
    }

    void addFeatureTemplateGenerator(shared_ptr<FeatureTemplateGenerator<T>> generator) {
        generatorList->push_back(generator);
    }
private:
    shared_ptr<vector<shared_ptr<FeatureTemplateGenerator<T>>>> generatorList;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_HIGH_ORDER_CRF_AGGREGATED_FEATURE_TEMPLATE_GENERATOR_H
