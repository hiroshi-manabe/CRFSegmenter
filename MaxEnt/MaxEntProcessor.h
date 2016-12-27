#ifndef HOCRF_MAX_ENT_MAX_ENT_PROCESSOR_H_
#define HOCRF_MAX_ENT_MAX_ENT_PROCESSOR_H_

#include "../Optimizer/OptimizerClass.h"
#include "../task/task_queue.hpp"
#include "CompiledData.h"
#include "MaxEntData.h"
#include "Observation.h"

#include <string>
#include <vector>

namespace MaxEnt {

class MaxEntData;

class MaxEntProcessor
{
 public:
    MaxEntProcessor();
    void train(const std::vector<Observation> &observationList,
               size_t concurrency,
               size_t maxIters,
               double regularizationCoefficientL1,
               double regularizationCoefficientL2,
               double epsilonForConvergence);

    std::string inferLabel(const Observation &obs) const;

    void writeModel(const std::string &filename);
    void readModel(const std::string &filename);

 private:
    std::shared_ptr<MaxEntData> modelData;
    std::shared_ptr<std::vector<double>> expWeightList;
    std::shared_ptr<std::vector<std::string>> labelStringList;
};

} // namespace MaxEnt

#endif // HOCRF_MAX_ENT_MAX_ENT_PROCESSOR_H_
