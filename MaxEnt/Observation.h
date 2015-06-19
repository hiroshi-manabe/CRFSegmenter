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
    struct hash<pair<uint32_t, uint32_t>> {
        size_t operator()(const pair<uint32_t, uint32_t> &p) const {
            return p.first ^ p.second;
        }
    };

}  // namespace std
#endif  // UINT_PAIR_KEY

namespace MaxEnt {

using std::ostream;
using std::pair;
using std::set;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;
class CompiledData;

class Observation
{
public:
    Observation(unordered_set<string> attributeSet, string correctLabel, set<string> possibleLabelSet);
    shared_ptr<CompiledData> compile(unordered_map<string, uint32_t> *labelToIndexMap,
                                     unordered_map<string, uint32_t> *attrToIndexMap,
                                     unordered_map<pair<uint32_t, uint32_t>, uint32_t> *indexPairToFeatureIndexMap,
                                     bool extendMap) const;
    void output(ostream &os);
    
private:
    unordered_set<string> attributeSet;
    string correctLabel;
    set<string> possibleLabelSet;
};

}  // namespace MaxEnt

#endif  // HOCRF_MAX_ENT_OBSERVATION_H_
