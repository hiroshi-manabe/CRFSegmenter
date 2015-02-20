#ifndef HOCRF_UNCONDITIONAL_FEATURE_TEMPLATE_GENERATOR_H_
#define HOCRF_UNCONDITIONAL_FEATURE_TEMPLATE_GENERATOR_H_

#include "types.h"

#include <algorithm>
#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::min;
using std::shared_ptr;
using std::vector;

class FeatureTemplate;

template <typename T>
class UnconditionalFeatureTemplateGenerator : public FeatureTemplateGenerator<T>
{
public:
    UnconditionalFeatureTemplateGenerator(size_t maxLabelLength) : maxLabelLength(maxLabelLength) {};
    virtual shared_ptr<vector<shared_ptr<FeatureTemplate>>> generateFeatureTemplatesAt(shared_ptr<vector<T>> observationList, size_t pos) const {
        auto templateList = make_shared<vector<shared_ptr<FeatureTemplate>>>();
        for (size_t i = 1; i <= min(maxLabelLength, pos + 1); ++i) {
            templateList->push_back(make_shared<FeatureTemplate>("", i));
        }
        return templateList;
    }
private:
    size_t maxLabelLength;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_UNCONDITIONAL_FEATURE_TEMPLATE_GENERATOR_H
