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
               size_t concurrency,
               size_t maxIter,
               double regularizationCoefficientL1,
               double regularizationCoefficientL2,
               double epsilonForConvergence);
    
    std::vector<std::string> tag(const std::vector<std::vector<std::string>> &seq) const;

    std::vector<std::string> tagFeatureTemplates(std::vector<std::vector<std::shared_ptr<FeatureTemplate>>> seq, std::vector<std::unordered_set<std::string>> possibleLabelSetList) const;

    std::vector<std::string> calcLabelLikelihoods(const std::vector<std::vector<std::string>> &seq);
    
    void test(const std::string &filename,
              size_t concurrency) const;

    void writeModel(const std::string &filename);

    void readModel(const std::string &filename);

private:
    std::vector<label_t> tagDataSequenceWithLabelType(const DataSequence &dataSequence) const;
    std::vector<std::string> tagDataSequence(const DataSequence &dataSequence) const;

    void prepareExpWeights();

    std::shared_ptr<HighOrderCRFData> modelData;
    std::shared_ptr<std::vector<double>> expWeights;  // only for likelihood calculation
};

} // namespace HighOrderCRF

#endif // HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_PROCESSOR_H_
