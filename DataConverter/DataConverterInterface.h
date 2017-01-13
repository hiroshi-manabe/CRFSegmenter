#ifndef HOCRF_DATA_CONVERTER_DATA_CONVERTER_INTERFACE_H_
#define HOCRF_DATA_CONVERTER_DATA_CONVERTER_INTERFACE_H_

#include <istream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "FeatureTemplateGenerator.h"
#include "../HighOrderCRF/DataSequence.h"

namespace DataConverter {

class DataConverterInterface {
public:
    virtual std::shared_ptr<HighOrderCRF::DataSequence> toDataSequence(const std::vector<std::string> &sequence) const = 0;
};

}  // namespace DataConverter
#endif  // HOCRF_DATA_CONVERTER_DATA_CONVERTER_INTERFACE_H_
