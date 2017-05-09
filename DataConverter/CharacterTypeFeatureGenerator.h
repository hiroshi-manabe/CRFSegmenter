#ifndef HOCRF_DATA_CONVERTER_CHARACTER_TYPE_FEATURE_GENERATOR_H_
#define HOCRF_DATA_CONVERTER_CHARACTER_TYPE_FEATURE_GENERATOR_H_

#include <memory>
#include <vector>

#include "FeatureTemplateGenerator.h"

namespace Utility {
class CharWithSpace;
}

namespace DataConverter {

class CharacterTypeFeatureGenerator : public FeatureTemplateGenerator<Utility::CharWithSpace> {
public:
    CharacterTypeFeatureGenerator(size_t maxNgram, size_t maxWindow, size_t maxLabelLength);
    virtual std::vector<std::vector<HighOrderCRF::FeatureTemplate>> generateFeatureTemplates(const std::vector<Utility::CharWithSpace> &observationList) const;

private:
    size_t maxNgram;
    size_t maxWindow;
    size_t maxLabelLength;
};

}  // namespace DataConverter

#endif  // HOCRF_DATA_CONVERTER_CHARACTER_TYPE_FEATURE_GENERATOR_H_
