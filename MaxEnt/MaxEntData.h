#ifndef HOCRF_MAX_ENT_MAX_ENT_DATA_H_
#define HOCRF_MAX_ENT_MAX_ENT_DATA_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace MaxEnt {

using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

class MaxEntData
{
public:
    MaxEntData();
    MaxEntData(shared_ptr<unordered_map<string, size_t>> strToIndexMap, shared_ptr<vector<double>> bestWeightList);
    void read(const string &filename);
    void write(const string &filename) const;
    const shared_ptr<vector<double>> getBestWeightList() const;
    shared_ptr<unordered_map<string, size_t>> getStrToIndexMap();
    void dumpFeatures(const string &filename, bool outputWeights) const;
    
private:
    shared_ptr<unordered_map<string, size_t>> strToIndexMap;
    shared_ptr<vector<double>> bestWeightList;
};

}  // namespace MaxEnt
#endif  // HOCRF_MAX_ENT_MAX_ENT_DATA_H_
