#ifndef HOCRF_DATA_CONVERTER_CHAR_WITH_SPACE_FEATURE_GENERATOR_H_
#define HOCRF_DATA_CONVERTER_CHAR_WITH_SPACE_FEATURE_GENERATOR_H_

#include <vector>

#include "FeatureTemplateGenerator.h"

namespace Utility {
class CharWithSpace;
}

namespace DataConverter {

class CharWithSpaceFeatureGenerator : public FeatureTemplateGenerator<Utility::CharWithSpace> {
public:
    CharWithSpaceFeatureGenerator(size_t maxNgram, size_t maxWindow, size_t maxLabelLength);
    virtual std::vector<std::vector<HighOrderCRF::FeatureTemplate>> generateFeatureTemplates(const std::vector<Utility::CharWithSpace> &observationList) const;

private:
    size_t maxNgram;
    size_t maxWindow;
    size_t maxLabelLength;
};

}  // namespace DataConverter

#endif  // HOCRF_DATA_CONVERTER_CHAR_WITH_SPACE_FEATURE_GENERATOR_H_
