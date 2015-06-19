#ifndef HOCRF_MAX_ENT_MAX_ENT_DATA_H_
#define HOCRF_MAX_ENT_MAX_ENT_DATA_H_

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#ifndef UINT_PAIR_KEY
#define UINT_PAIR_KEY
namespace std {
    template<>
    struct hash <pair<uint32_t, uint32_t>> {
        size_t operator()(const pair<uint32_t, uint32_t> &p) const {
            return p.first ^ p.second;
        }
    };
}
#endif  // UINT_PAIR_KEY

namespace MaxEnt {

using std::pair;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

class MaxEntData
{
public:
    MaxEntData();
    MaxEntData(unordered_map<string, uint32_t> labelToIndexMap,
               unordered_map<string, uint32_t> attrToIndexMap,
               unordered_map<pair<uint32_t, uint32_t>, uint32_t> indexPairToFeatureIndexMap,
               vector<double> bestWeightList);
    void read(const string &filename);
    void trim();
    void write(const string &filename) const;
    const vector<double> &getBestWeightList() const;
    unordered_map<string, uint32_t> &getLabelToIndexMap();
    unordered_map<string, uint32_t> &getAttrToIndexMap();
    unordered_map<pair<uint32_t, uint32_t>, uint32_t> &getIndexPairToFeatureIndexMap();
    
private:
    unordered_map<string, uint32_t> labelToIndexMap;
    unordered_map<string, uint32_t> attrToIndexMap;
    unordered_map<pair<uint32_t, uint32_t>, uint32_t> indexPairToFeatureIndexMap;
    vector<double> bestWeightList;
};

}  // namespace MaxEnt

#endif  // HOCRF_MAX_ENT_MAX_ENT_DATA_H_
