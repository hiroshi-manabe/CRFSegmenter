#ifndef HOCRF_DATA_CONVERTER_SEGMENTER_DATA_CONVERTER_H_
#define HOCRF_DATA_CONVERTER_SEGMENTER_DATA_CONVERTER_H_

#include <istream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../HighOrderCRF/DataSequence.h"
#include "CharWithSpace.h"
#include "DataConverterInterface.h"
#include "FeatureTemplateGenerator.h"

namespace DataConverter {

class SegmenterDataConverter : public DataConverterInterface {
public:
    virtual std::shared_ptr<HighOrderCRF::DataSequence> toDataSequence(const std::vector<std::string> &sequence) const;
    void setOptions(const std::unordered_map<std::string, std::string> &options);

private:
    std::shared_ptr<FeatureTemplateGenerator<CharWithSpace>> generator;
    std::unordered_map<std::string, std::string> options;
    bool optionSet;
};
    
}  // namespace DataConverter
#endif  // HOCRF_DATA_CONVERTER_SEGMENTER_DATA_CONVERTER_H_
