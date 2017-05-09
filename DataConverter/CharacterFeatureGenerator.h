#ifndef HOCRF_DATA_CONVERTER_CHARACTER_FEATURE_GENERATOR_H_
#define HOCRF_DATA_CONVERTER_CHARACTER_FEATURE_GENERATOR_H_

#include <vector>

#include "FeatureTemplateGenerator.h"

namespace Utility {
class CharWithSpace;
}

namespace DataConverter {

class CharacterFeatureGenerator : public FeatureTemplateGenerator<Utility::CharWithSpace> {
public:
    CharacterFeatureGenerator(size_t maxNgram, size_t maxWindow, size_t maxLabelLength);
    virtual std::vector<std::vector<HighOrderCRF::FeatureTemplate>> generateFeatureTemplates(const std::vector<Utility::CharWithSpace> &observationList) const;

private:
    size_t maxNgram;
    size_t maxWindow;
    size_t maxLabelLength;
};

}  // namespace DataConverter

#endif  // HOCRF_DATA_CONVERTER_CHARACTER_FEATURE_GENERATOR_H_
