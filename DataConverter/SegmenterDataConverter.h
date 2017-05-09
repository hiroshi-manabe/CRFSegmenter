#ifndef HOCRF_DATA_CONVERTER_SEGMENTER_DATA_CONVERTER_H_
#define HOCRF_DATA_CONVERTER_SEGMENTER_DATA_CONVERTER_H_

#include <istream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../HighOrderCRF/DataSequence.h"
#include "DataConverterInterface.h"
#include "FeatureTemplateGenerator.h"

namespace Utility {
class CharWithSpace;
}

namespace DataConverter {

class SegmenterDataConverter : public DataConverterInterface {
public:
    SegmenterDataConverter(const std::unordered_map<std::string, std::string> &options, const std::unordered_set<std::string> &dictionaries);
    virtual std::shared_ptr<HighOrderCRF::DataSequence> toDataSequence(const std::vector<std::string> &sequence) const;

private:
    std::shared_ptr<FeatureTemplateGenerator<Utility::CharWithSpace>> generator;
    std::unordered_map<std::string, std::string> options;
    std::unordered_set<std::string> dictionaries;
};
    
}  // namespace DataConverter
#endif  // HOCRF_DATA_CONVERTER_SEGMENTER_DATA_CONVERTER_H_
