#ifndef HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_PROCESSOR_H_
#define HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_PROCESSOR_H_

#include "types.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace HighOrderCRF {

class DataSequence;
class HighOrderCRFData;

class HighOrderCRFProcessor
{
public:
    HighOrderCRFProcessor();
    void train(const std::string &filename,
               size_t concurrency,
               size_t maxIter,
               bool useL1Regularization,
               double regularizationCoefficient,
               double epsilonForConvergence);
    
    std::vector<std::string> tag(const std::vector<std::vector<std::string>> &seq) const;

    std::vector<std::string> calcLabelLikelihoods(const std::vector<std::vector<std::string>> &seq);
    
    void test(const std::string &filename,
              size_t concurrency) const;

    void writeModel(const std::string &filename);

    void readModel(const std::string &filename);

private:
    std::vector<label_t> tagLabelType(const DataSequence &dataSequence) const;

    void prepareExpWeights();

    std::shared_ptr<HighOrderCRFData> modelData;
    std::shared_ptr<std::vector<double>> expWeights;  // only for likelihood calculation
};

} // namespace HighOrderCRF

#endif // HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_PROCESSOR_H_
