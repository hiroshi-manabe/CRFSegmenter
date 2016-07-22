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
    struct hash <std::pair<uint32_t, uint32_t>> {
        size_t operator()(const std::pair<uint32_t, uint32_t> &p) const {
            return p.first ^ p.second;
        }
    };
}
#endif  // UINT_PAIR_KEY

namespace MaxEnt {

class MaxEntData
{
public:
    MaxEntData();
    MaxEntData(std::unordered_map<std::string, uint32_t> labelToIndexMap,
               std::unordered_map<std::string, uint32_t> attrToIndexMap,
               std::unordered_map<std::pair<uint32_t, uint32_t>, uint32_t> indexPairToFeatureIndexMap,
               std::vector<double> bestWeightList);
    void read(const std::string &filename);
    void trim();
    void write(const std::string &filename) const;
    const std::vector<double> &getBestWeightList() const;
    std::unordered_map<std::string, uint32_t> &getLabelToIndexMap();
    std::unordered_map<std::string, uint32_t> &getAttrToIndexMap();
    std::unordered_map<std::pair<uint32_t, uint32_t>, uint32_t> &getIndexPairToFeatureIndexMap();
    
private:
    std::unordered_map<std::string, uint32_t> labelToIndexMap;
    std::unordered_map<std::string, uint32_t> attrToIndexMap;
    std::unordered_map<std::pair<uint32_t, uint32_t>, uint32_t> indexPairToFeatureIndexMap;
    std::vector<double> bestWeightList;
};

}  // namespace MaxEnt

#endif  // HOCRF_MAX_ENT_MAX_ENT_DATA_H_
