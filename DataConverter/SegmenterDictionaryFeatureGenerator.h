#ifndef HOCRF_DATA_CONVERTER_SEGMENTER_DICTIONARY_FEATURE_GENERATOR_H_
#define HOCRF_DATA_CONVERTER_SEGMENTER_DICTIONARY_FEATURE_GENERATOR_H_

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../Dictionary/DictionaryClass.h"
#include "CharWithSpace.h"
#include "FeatureTemplateGenerator.h"

namespace DataConverter {

class SegmenterDictionaryFeatureGenerator : public FeatureTemplateGenerator<CharWithSpace> {
public:
    SegmenterDictionaryFeatureGenerator(const std::string &dictionaryFile, size_t maxLabelLength);
    virtual std::vector<std::vector<HighOrderCRF::FeatureTemplate>> generateFeatureTemplates(const std::vector<CharWithSpace> &observationList) const;

private:
    std::shared_ptr<Dictionary::DictionaryClass> dictionary;
    size_t maxLabelLength;
};

}  // namespace DataConverter

#endif  // HOCRF_DATA_CONVERTER_SEGMENTER_DICTIONARY_FEATURE_GENERATOR_H_
