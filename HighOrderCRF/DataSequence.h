#ifndef HOCRF_HIGH_ORDER_CRF_DATA_SEQUENCE_H
#define HOCRF_HIGH_ORDER_CRF_DATA_SEQUENCE_H

#include "types.h"

#include "Feature.h"
#include "FeatureTemplate.h"
#include "InternalDataSequence.h"
#include "LabelSequence.h"
#include "PatternSetSequence.h"

#include <istream>
#include <ostream>
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

namespace HighOrderCRF {

class DataSequence
{
public:
    DataSequence(std::vector<std::string> originalStringList,
                 std::vector<std::string> labels,
                 std::vector<std::set<std::string>> possibleLabelTypeSetList,
                 std::vector<std::vector<FeatureTemplate>> featureTemplateListList);
    DataSequence(std::istream &is);
    void write(std::ostream &os) const;
    // This method destroys the original object
    InternalDataSequence toInternalDataSequence(const std::unordered_map<std::string, label_t> &labelMap);
    const std::vector<std::string> &getLabels() const;
    const std::vector<std::string> &getOriginalStringList() const;
    std::unordered_set<std::string> getUsedLabelSet() const;
    size_t length() const;
    bool empty() const;
private:
    std::vector<std::string> originalStringList;
    std::vector<std::string> labels;
    std::vector<std::set<std::string>> possibleLabelSetList;
    std::vector<std::vector<FeatureTemplate>> featureTemplateListList;
};

}  // namespace HighOrderCRF
#endif  // HOCRF_HIGH_ORDER_CRF_DATA_SEQUENCE_H
