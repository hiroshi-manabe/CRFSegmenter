#ifndef HOCRF_DATA_CONVERTER_CHARACTER_TYPE_FEATURE_GENERATOR_H_
#define HOCRF_DATA_CONVERTER_CHARACTER_TYPE_FEATURE_GENERATOR_H_

#include <memory>
#include <vector>

#include "CharWithSpace.h"
#include "FeatureTemplateGenerator.h"

namespace DataConverter {

class CharacterTypeFeatureGenerator : public FeatureTemplateGenerator<CharWithSpace> {
public:
    CharacterTypeFeatureGenerator(size_t maxNgram, size_t maxWindow, size_t maxLabelLength);
    virtual std::vector<std::vector<HighOrderCRF::FeatureTemplate>> generateFeatureTemplates(const std::vector<CharWithSpace> &observationList) const;

private:
    size_t maxNgram;
    size_t maxWindow;
    size_t maxLabelLength;
};

}  // namespace DataConverter

#endif  // HOCRF_DATA_CONVERTER_CHARACTER_TYPE_FEATURE_GENERATOR_H_
