#ifndef HOCRF_MAX_ENT_COMPILED_DATA_H_
#define HOCRF_MAX_ENT_COMPILED_DATA_H_

#include <cstdint>
#include <string>
#include <vector>

namespace MaxEnt {

class CompiledData
{
public:
    CompiledData(std::vector<std::vector<uint32_t>> featureIndexListList,
                 std::vector<std::string> labelStringList,
                 size_t correctLabelIndex);
    void accumulateFeatureCounts(double *counts) const;
    double accumulateFeatureExpectations(const double *expWeights, double *expectations) const;
    const std::string &inferLabel(const double *expWeights) const;
    
private:
    std::vector<std::vector<uint32_t>> featureIndexListList;
    std::vector<std::string> labelStringList;
    size_t correctLabelIndex;
};

}  // namespace MaxEnt
#endif  // HOCRF_MAX_ENT_COMPILED_DATA_H_
