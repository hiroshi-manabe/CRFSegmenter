#ifndef HOCRF_HIGH_ORDER_CRF_DATA_SEQUENCE_H
#define HOCRF_HIGH_ORDER_CRF_DATA_SEQUENCE_H

#include "types.h"

#include "Feature.h"
#include "FeatureTemplate.h"
#include "LabelSequence.h"
#include "PatternSetSequence.h"

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace HighOrderCRF {

class DataSequence
{
public:
    DataSequence(std::vector<std::vector<std::shared_ptr<FeatureTemplate>>> featureTemplateListList,
                 std::vector<label_t> labels,
                 std::vector<std::unordered_set<label_t>> possibleLabelTypeSetList,
                 bool hasValidLabels);
    size_t length() const;
    std::shared_ptr<LabelSequence> getLabelSequence(size_t pos, size_t length) const;
    void accumulateFeatureData(std::unordered_map<std::shared_ptr<FeatureTemplate>, std::vector<uint32_t>> *featureTemplateToFeatureIndexListMap, std::unordered_map<std::shared_ptr<Feature>, uint32_t> *featureToFeatureIndexMap, std::vector<double> *featureCountList) const;
    std::shared_ptr<PatternSetSequence> generatePatternSetSequence(const std::unordered_map<std::shared_ptr<FeatureTemplate>, std::vector<uint32_t>> &featureTemplateToFeatureIndexListMap, const std::vector<uint32_t> &featureLabelSequenceIndexList, const std::vector<LabelSequence> &labelSequenceList) const;
    std::vector<label_t> getAllLabels() const;
private:
    std::vector<std::vector<std::shared_ptr<FeatureTemplate>>> featureTemplateListList;
    std::vector<label_t> labels;
    bool hasValidLabels;
    std::vector<std::unordered_set<label_t>> possibleLabelSetList;
private:
};

}  // namespace HighOrderCRF
#endif  // HOCRF_HIGH_ORDER_CRF_DATA_SEQUENCE_H
