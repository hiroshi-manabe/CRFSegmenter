#ifndef HOCRF_FEATURE_TEMPLATE_GENERATOR_H_
#define HOCRF_FEATURE_TEMPLATE_GENERATOR_H_

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
    virtual shared_ptr<vector<shared_ptr<FeatureTemplate>>> generateFeatureTemplatesAt(shared_ptr<vector<T>> observationList, size_t pos) const = 0;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_FEATURE_TEMPLATE_GENERATOR_H
