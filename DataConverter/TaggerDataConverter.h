#ifndef HOCRF_DATA_CONVERTER_TAGGER_DATA_CONVERTER_H_
#define HOCRF_DATA_CONVERTER_TAGGER_DATA_CONVERTER_H_

#include <istream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../Dictionary/DictionaryClass.h"
#include "CharWithSpace.h"
#include "DataConverterInterface.h"
#include "FeatureTemplateGenerator.h"

namespace DataConverter {

class TaggerDataConverter : public DataConverterInterface {
public:
    virtual void setOptions(const std::unordered_map<std::string, std::string> &options);
    virtual std::vector<std::string> generateFeaturesFromStream(std::istream& is) const;

    std::unordered_map<std::string, std::string> options;

private:
    std::vector<std::string> generateFeaturesFromSequence(const std::vector<std::string> &sequence) const;
    std::shared_ptr<FeatureTemplateGenerator<std::string>> generator;
    std::shared_ptr<Dictionary::DictionaryClass> dictionary;
    bool optionSet;
};
    
}  // namespace DataConverter
#endif  // HOCRF_DATA_CONVERTER_TAGGER_DATA_CONVERTER_H_
