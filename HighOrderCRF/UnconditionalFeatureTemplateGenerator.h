#ifndef HOCRF_UNCONDITIONAL_FEATURE_TEMPLATE_GENERATOR_H_
#define HOCRF_UNCONDITIONAL_FEATURE_TEMPLATE_GENERATOR_H_

#include "types.h"
#include "FeatureTemplate.h"

#include <algorithm>
#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::min;
using std::shared_ptr;
using std::vector;

template <typename T>
class UnconditionalFeatureTemplateGenerator : public FeatureTemplateGenerator<T>
{
public:
    UnconditionalFeatureTemplateGenerator(size_t maxLabelLength) : maxLabelLength(maxLabelLength) {};
    virtual shared_ptr<vector<vector<shared_ptr<FeatureTemplate>>>> generateFeatureTemplates(shared_ptr<vector<T>> observationList) const {
        auto templateListList = make_shared<vector<vector<shared_ptr<FeatureTemplate>>>>(observationList->size());
        for (size_t pos = 0; pos < observationList->size(); ++pos) {
            for (size_t i = 1; i <= min(maxLabelLength, pos + 1); ++i) {
                (*templateListList)[pos].push_back(make_shared<FeatureTemplate>("", i));
            }
        }
        return templateListList;
    }
private:
    size_t maxLabelLength;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_UNCONDITIONAL_FEATURE_TEMPLATE_GENERATOR_H
