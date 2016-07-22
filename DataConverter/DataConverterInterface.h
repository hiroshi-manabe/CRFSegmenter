#ifndef HOCRF_DATA_CONVERTER_DATA_CONVERTER_INTERFACE_H_
#define HOCRF_DATA_CONVERTER_DATA_CONVERTER_INTERFACE_H_

#include <istream>
#include <string>
#include <unordered_map>
#include <vector>

#include "FeatureTemplateGenerator.h"

namespace DataConverter {

class DataConverterInterface {
public:
    virtual void setOptions(const std::unordered_map<std::string, std::string> &options) = 0;
    virtual std::vector<std::string> generateFeaturesFromStream(std::istream& is) const = 0;
};
    
}  // namespace DataConverter
#endif  // HOCRF_DATA_CONVERTER_DATA_CONVERTER_INTERFACE_H_
