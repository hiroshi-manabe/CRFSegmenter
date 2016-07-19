#ifndef HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_PROCESSOR_H_
#define HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_PROCESSOR_H_

#include "types.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace HighOrderCRF {

using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

class DataSequence;
class HighOrderCRFData;

class HighOrderCRFProcessor
{
public:
    HighOrderCRFProcessor();
    void train(const string &filename,
               size_t concurrency,
               size_t maxIter,
               bool useL1Regularization,
               double regularizationCoefficient,
               double epsilonForConvergence);
    
    vector<string> tag(const vector<string> &seq) const;

    vector<string> calcLabelLikelihoods(const vector<string> &seq);
    
    void test(const string &filename,
              size_t concurrency) const;

    void writeModel(const string &filename);

    void readModel(const string &filename);

private:
    vector<label_t> tagLabelType(const DataSequence &dataSequence) const;

    void prepareExpWeights();

    shared_ptr<HighOrderCRFData> modelData;
    shared_ptr<vector<double>> expWeights;  // only for likelihood calculation
};

} // namespace HighOrderCRF

#endif // HOCRF_HIGH_ORDER_CRF_HIGH_ORDER_CRF_PROCESSOR_H_
