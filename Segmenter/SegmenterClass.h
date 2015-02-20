#ifndef SEGMENTER_SEGMENTER_H_
#define SEGMENTER_SEGMENTER_H_

#include <memory>
#include <string>
#include <vector>

#include "../HighOrderCRF/FeatureTemplateGenerator.h"

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

struct TrainingOptions;
class UnicodeCharacter;

class SegmenterClass {

public:
    SegmenterClass(const TrainingOptions &trainingOptions);
    shared_ptr<vector<shared_ptr<ObservationSequence<UnicodeCharacter>>>> readData(const string &fileName, bool hasValidLabels);
    void train(const string &trainingFilename, const string &modelFilename);
    string segment(const string &line) const;
    void test(const string &testFilename);
    void readModel(const string &modelFilename);

private:
    shared_ptr<FeatureTemplateGenerator<UnicodeCharacter>> featureGenerator;
    shared_ptr<HighOrderCRFProcessor<UnicodeCharacter>> CRFProcessor;
};

}

#endif  // SEGMENTER_SEGMENTER_H_
