#ifndef HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_PROCESSOR_H_
#define HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_PROCESSOR_H_

#include "types.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace HighOrderCRF {

class DataSequence;
class FeatureTemplate;
class HighOrderCRFData;

class HighOrderCRFProcessor
{
public:
    HighOrderCRFProcessor();
    void train(const std::string &filename,
               size_t cutoff,
               size_t concurrency,
               size_t maxIter,
               double regularizationCoefficientL1,
               double regularizationCoefficientL2,
               double epsilonForConvergence);
    void test(const std::string &filename,
              size_t concurrency) const;
    void writeModel(const std::string &filename);
    void readModel(const std::string &filename);
    // dataSequence will be destroyed
    std::vector<std::string> tag(DataSequence *dataSequence) const;
    // dataSequence will be destroyed
    std::vector<std::unordered_map<std::string, double>> calcLabelLikelihoods(DataSequence *dataSequence) const;

private:
    std::shared_ptr<HighOrderCRFData> modelData;
};

} // namespace HighOrderCRF

#endif // HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_PROCESSOR_H_
