#ifndef HOCRF_MAX_ENT_OBSERVATION_H_
#define HOCRF_MAX_ENT_OBSERVATION_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace MaxEnt {

using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;
class CompiledData;

class Observation
{
public:
    Observation(unordered_set<string> attributeSet, string correctLabel, unordered_set<string> possibleLabelSet);
    shared_ptr<CompiledData> compile(shared_ptr<unordered_map<string, size_t>> strToIndexMap, bool extendMap) const;
    
private:
    unordered_set<string> attributeSet;
    string correctLabel;
    unordered_set<string> possibleLabelSet;
};

}  // namespace MaxEnt
#endif  // HOCRF_MAX_ENT_OBSERVATION_H_
