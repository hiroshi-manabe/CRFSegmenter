#ifndef HOCRF_DATA_CONVERTER_WORD_FEATURE_GENERATOR_H_
#define HOCRF_DATA_CONVERTER_WORD_FEATURE_GENERATOR_H_

#include <memory>
#include <string>
#include <vector>

#include "FeatureTemplateGenerator.h"

namespace DataConverter {

class WordFeatureGenerator : public FeatureTemplateGenerator<std::string> {
public:
    WordFeatureGenerator(size_t maxNgram, size_t maxWindow, size_t maxLabelLength);
    virtual std::vector<std::vector<HighOrderCRF::FeatureTemplate>> generateFeatureTemplates(const std::vector<std::string> &observationList) const;

private:
    size_t maxNgram;
    size_t maxWindow;
    size_t maxLabelLength;
};

}

#endif  // HOCRF_DATA_CONVERTER_WORD_FEATURE_GENERATOR_H_
