#ifndef HOCRF_DATA_CONVERTER_WORD_CHARACTER_TYPE_FEATURE_GENERATOR_H_
#define HOCRF_DATA_CONVERTER_WORD_CHARACTER_TYPE_FEATURE_GENERATOR_H_

#include <memory>
#include <string>
#include <vector>

#include "FeatureTemplateGenerator.h"

namespace DataConverter {

class WordCharacterTypeFeatureGenerator : public FeatureTemplateGenerator<std::string> {
public:
    WordCharacterTypeFeatureGenerator(size_t maxLength);
    virtual std::vector<std::vector<HighOrderCRF::FeatureTemplate>> generateFeatureTemplates(const std::vector<std::string> &observationList) const;

private:
    size_t maxLength;
};

}

#endif  // HOCRF_DATA_CONVERTER_WORD_CHARACTER_TYPE_FEATURE_GENERATOR_H_
