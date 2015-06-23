#ifndef HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_DATA_H_
#define HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_DATA_H_

#include "types.h"
#include "FeatureTemplate.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace HighOrderCRF {

using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

class HighOrderCRFData {
public:
    HighOrderCRFData(unordered_map<shared_ptr<FeatureTemplate>, vector<uint32_t>> featureTemplateToFeatureIndexListMap, vector<double> weightList, vector<uint32_t> featureLabelSequenceIndexList, vector<LabelSequence> labelSequenceList, unordered_map<string, label_t> labelMap);
    HighOrderCRFData();

    const unordered_map<shared_ptr<FeatureTemplate>, vector<uint32_t>> &getFeatureTemplateToFeatureIndexMapList() const;
    const vector<weight_t> &getWeightList() const;
    const vector<uint32_t> &getFeatureLabelSequenceIndexList() const;
    const vector<LabelSequence> &getLabelSequenceList() const;
    const unordered_map<string, label_t> &getLabelMap() const;
    vector<string> getLabelStringList() const;
    void trim();
    void read(const string &filename);
    void write(const string &filename) const;
    void dumpFeatures(const string &filename, bool outputWeights) const;

private:
    unordered_map<shared_ptr<FeatureTemplate>, vector<uint32_t>> featureTemplateToFeatureIndexListMap;
    vector<weight_t> weightList;
    vector<uint32_t> featureLabelSequenceIndexList;
    vector<LabelSequence> labelSequenceList;
    unordered_map<string, label_t> labelMap;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_DATA_H_
