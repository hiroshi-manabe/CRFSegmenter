#ifndef HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_DATA_H_
#define HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_DATA_H_

#include "types.h"
#include "FeatureTemplate.h"
#include "LabelSequence.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace HighOrderCRF {

class HighOrderCRFData {
public:
    HighOrderCRFData(std::unordered_map<FeatureTemplate, std::vector<uint32_t>> featureTemplateToFeatureIndexListMap, std::vector<double> weightList, std::vector<uint32_t> featureLabelSequenceIndexList, std::vector<LabelSequence> labelSequenceList, std::unordered_map<std::string, label_t> labelMap);
    HighOrderCRFData();

    const std::unordered_map<FeatureTemplate, std::vector<uint32_t>> &getFeatureTemplateToFeatureIndexMapList() const;
    const std::vector<weight_t> &getWeightList() const;
    const std::vector<double> &getExpWeightList() const;
    const std::vector<uint32_t> &getFeatureLabelSequenceIndexList() const;
    const std::vector<LabelSequence> &getLabelSequenceList() const;
    const std::unordered_map<std::string, label_t> &getLabelMap() const;
    std::vector<std::string> HighOrderCRFData::getLabelStringList() const;
    void trim();
    void read(const std::string &filename);
    void write(const std::string &filename) const;
    void dumpFeatures(const std::string &filename, bool outputWeights) const;

private:
    void setExpWeightList();
    std::unordered_map<FeatureTemplate, std::vector<uint32_t>> featureTemplateToFeatureIndexListMap;
    std::vector<weight_t> weightList;
    std::vector<double> expWeightList;
    std::vector<uint32_t> featureLabelSequenceIndexList;
    std::vector<LabelSequence> labelSequenceList;
    std::unordered_map<std::string, label_t> labelMap;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_DATA_H_
