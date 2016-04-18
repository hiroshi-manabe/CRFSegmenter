#ifndef HOCRF_SEGMENTER_SEGMENTER_CLASS_H_
#define HOCRF_SEGMENTER_SEGMENTER_CLASS_H_

#include <memory>
#include <string>
#include <vector>

#include "../HighOrderCRF/FeatureTemplateGenerator.h"
#include "SegmenterOptions.h"

namespace HighOrderCRF {

template <typename T>
class ObservationSequence;
template <typename T>
class HighOrderCRFProcessor;

}


namespace Segmenter {

using HighOrderCRF::FeatureTemplateGenerator;
using HighOrderCRF::HighOrderCRFProcessor;
using HighOrderCRF::ObservationSequence;

using std::shared_ptr;
using std::string;
using std::vector;

class CharWithSpace;

class SegmenterClass {

public:
    SegmenterClass(const SegmenterOptions &segmenterOptions);
    void train(const string &trainingFilename, const string &modelFilename);
    string segment(const string &line) const;
    string calcLabelLikelihoods(const string &line);
    void test(const string &testFilename);
    void readModel(const string &modelFilename);

private:
    shared_ptr<FeatureTemplateGenerator<CharWithSpace>> featureGenerator;
    shared_ptr<HighOrderCRFProcessor<CharWithSpace>> CRFProcessor;
    SegmenterOptions options;
};

}

#endif  // HOCRF_SEGMENTER_SEGMENTER_CLASS_H_
