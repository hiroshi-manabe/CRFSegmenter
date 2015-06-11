#ifndef HOCRF_HIGH_ORDER_CRF_FEATURE_TEMPLATE_GENERATOR_H_
#define HOCRF_HIGH_ORDER_CRF_FEATURE_TEMPLATE_GENERATOR_H_

#include "types.h"

#include "FeatureTemplate.h"

#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::shared_ptr;
using std::vector;

template <typename T>
class FeatureTemplateGenerator
{
public:
    virtual shared_ptr<vector<vector<shared_ptr<FeatureTemplate>>>> generateFeatureTemplates(shared_ptr<vector<T>> observationList) const = 0;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_HIGH_ORDER_CRF_FEATURE_TEMPLATE_GENERATOR_H
