#ifndef HOCRF_MAX_ENT_COMPILED_DATA_H_
#define HOCRF_MAX_ENT_COMPILED_DATA_H_

#include <memory>
#include <string>
#include <vector>

namespace MaxEnt {

using std::shared_ptr;
using std::string;
using std::vector;

class CompiledData
{
public:
    CompiledData(vector<vector<size_t>> featureIndexListList,
                 vector<string> labelStringList,
                 size_t correctLabelIndex);
    void accumulateFeatureCounts(double *counts) const;
    double accumulateFeatureExpectations(const double *expWeights, double *expectations) const;
    const string &inferLabel(const double *expWeights) const;
    
private:
    vector<vector<size_t>> featureIndexListList;
    vector<string> labelStringList;
    size_t correctLabelIndex;
};

}  // namespace MaxEnt
#endif  // HOCRF_MAX_ENT_COMPILED_DATA_H_
