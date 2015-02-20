#ifndef HOCRF_HIGH_ORDER_CRF_DATA_H_
#define HOCRF_HIGH_ORDER_CRF_DATA_H_

#include "types.h"
#include "Feature.h"

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
    HighOrderCRFData(shared_ptr<vector<shared_ptr<Feature>>> featureList, shared_ptr<vector<double>> bestWeightList, shared_ptr<unordered_map<string, label_t>> labelMap);
    HighOrderCRFData();

    shared_ptr<vector<shared_ptr<Feature>>> getFeatureList() const;
    shared_ptr<vector<double>> getBestWeightList() const;
    shared_ptr<unordered_map<string, label_t>> getLabelMap() const;
    shared_ptr<vector<string>> getLabelStringList() const;
    void read(const string &filename);
    void write(const string &filename) const;
    void dumpFeatures(const string &filename) const;

private:
    shared_ptr<vector<shared_ptr<Feature>>> featureList;
    shared_ptr<vector<double>> bestWeightList;
    shared_ptr<unordered_map<string, label_t>> labelMap;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_HIGH_ORDER_CRF_DATA_H_
