#ifndef HOCRF_DATA_CONVERTER_TAGGER_DATA_CONVERTER_H_
#define HOCRF_DATA_CONVERTER_TAGGER_DATA_CONVERTER_H_

#include <istream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../Dictionary/DictionaryClass.h"
#include "CharWithSpace.h"
#include "DataConverterInterface.h"
#include "FeatureTemplateGenerator.h"

namespace DataConverter {

class TaggerDataConverter : public DataConverterInterface {
public:
    TaggerDataConverter(const std::unordered_map<std::string, std::string> &options, const std::unordered_set<std::string> &dictionaries);
    virtual std::shared_ptr<HighOrderCRF::DataSequence> toDataSequence(const std::vector<std::string> &sequence) const;

private:
    std::shared_ptr<FeatureTemplateGenerator<std::string>> generator;
    std::shared_ptr<Dictionary::DictionaryClass> dictionary;
    std::unordered_map<std::string, std::string> options;
    bool optionSet;
};
    
}  // namespace DataConverter
#endif  // HOCRF_DATA_CONVERTER_TAGGER_DATA_CONVERTER_H_
