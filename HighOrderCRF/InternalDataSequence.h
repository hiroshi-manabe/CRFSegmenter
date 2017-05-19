#ifndef HOCRF_HIGH_ORDER_CRF_INTERNAL_DATA_SEQUENCE_H
#define HOCRF_HIGH_ORDER_CRF_INTERNAL_DATA_SEQUENCE_H

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

class InternalDataSequence
{
public:
    // arguments will be destroyed
    InternalDataSequence(std::vector<label_t> labelList, std::vector<std::unordered_set<label_t>> possibleLabelSetList, std::vector<std::vector<FeatureTemplate>> featureTemplateListList);
    size_t length() const;
    LabelSequence getLabelSequence(size_t pos, size_t length) const;
    void accumulateFeatureData(std::unordered_map<FeatureTemplate, std::vector<uint32_t>> *featureTemplateToFeatureIndexListMap, std::unordered_map<Feature, uint32_t> *featureToFeatureIndexMap, std::vector<uint32_t> *featureCountList) const;
    std::shared_ptr<PatternSetSequence> generatePatternSetSequence(const std::unordered_map<FeatureTemplate, std::vector<uint32_t>> &featureTemplateToFeatureIndexListMap, const std::vector<uint32_t> &featureLabelSequenceIndexList, const std::vector<LabelSequence> &labelSequenceList, bool hasValidLabels) const;
    const std::vector<label_t> &getLabels() const;
private:
    std::vector<label_t> labels;
    std::vector<std::unordered_set<label_t>> possibleLabelSetList;
    std::vector<std::vector<FeatureTemplate>> featureTemplateListList;
private:
};

}  // namespace HighOrderCRF
#endif  // HOCRF_HIGH_ORDER_CRF_INTERNAL_DATA_SEQUENCE_H
