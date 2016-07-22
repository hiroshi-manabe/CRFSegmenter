#ifndef HOCRF_MAX_ENT_OBSERVATION_H_
#define HOCRF_MAX_ENT_OBSERVATION_H_

#include <cstdint>
#include <memory>
#include <ostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

#ifndef UINT_PAIR_KEY
#define UINT_PAIR_KEY
namespace std {

    template<>
    struct hash<std::pair<uint32_t, uint32_t>> {
        size_t operator()(const std::pair<uint32_t, uint32_t> &p) const {
            return p.first ^ p.second;
        }
    };

}  // namespace std
#endif  // UINT_PAIR_KEY

namespace MaxEnt {

class CompiledData;

class Observation
{
public:
    Observation(std::unordered_set<std::string> attributeSet, std::string correctLabel, std::set<std::string> possibleLabelSet);
    std::shared_ptr<CompiledData> compile(std::unordered_map<std::string, uint32_t> *labelToIndexMap,
                                     std::unordered_map<std::string, uint32_t> *attrToIndexMap,
                                     std::unordered_map<std::pair<uint32_t, uint32_t>, uint32_t> *indexPairToFeatureIndexMap,
                                     bool extendMap) const;
    void output(std::ostream &os);
    
private:
    std::unordered_set<std::string> attributeSet;
    std::string correctLabel;
    std::set<std::string> possibleLabelSet;
};

}  // namespace MaxEnt

#endif  // HOCRF_MAX_ENT_OBSERVATION_H_
