#ifndef HOCRF_DATA_CONVERTER_DICTIONARY_FEATURE_GENERATOR_H_
#define HOCRF_DATA_CONVERTER_DICTIONARY_FEATURE_GENERATOR_H_

#include "../Dictionary/DictionaryClass.h"
#include "FeatureTemplateGenerator.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace DataConverter {

class DictionaryFeatureGenerator : public FeatureTemplateGenerator<std::string> {
public:
    DictionaryFeatureGenerator(std::shared_ptr<Dictionary::DictionaryClass> dictionary);
    virtual std::vector<std::vector<HighOrderCRF::FeatureTemplate>> generateFeatureTemplates(const std::vector<std::string> &observationList) const;

private:
    std::shared_ptr<Dictionary::DictionaryClass> dictionary;
};

}  // namespace DataConverter

#endif  // HOCRF_DATA_CONVERTER_DICTIONARY_FEATURE_GENERATOR_H_
