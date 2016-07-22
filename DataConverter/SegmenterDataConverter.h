#ifndef HOCRF_DATA_CONVERTER_SEGMENTER_DATA_CONVERTER_H_
#define HOCRF_DATA_CONVERTER_SEGMENTER_DATA_CONVERTER_H_

#include <istream>
#include <string>
#include <unordered_map>
#include <vector>

#include "CharWithSpace.h"
#include "DataConverterInterface.h"
#include "FeatureTemplateGenerator.h"

namespace DataConverter {

class SegmenterDataConverter : public DataConverterInterface {
public:
    virtual void setOptions(const std::unordered_map<std::string, std::string> &options);
    virtual std::vector<std::string> generateFeaturesFromStream(std::istream& is) const;

    std::unordered_map<std::string, std::string> options;

private:
    std::vector<std::string> generateFeaturesFromLine(const std::string &line) const;
    std::shared_ptr<FeatureTemplateGenerator<CharWithSpace>> generator;
    bool optionSet;
};
    
}  // namespace DataConverter
#endif  // HOCRF_DATA_CONVERTER_SEGMENTER_DATA_CONVERTER_H_
