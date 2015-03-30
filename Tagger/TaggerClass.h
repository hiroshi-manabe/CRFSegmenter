#ifndef TAGGER_TAGGER_CLASS_H_
#define TAGGER_TAGGER_CLASS_H_

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "../Dictionary/DictionaryClass.h"
#include "../HighOrderCRF/FeatureTemplateGenerator.h"
#include "TaggerOptions.h"

namespace HighOrderCRF {

template <typename T>
class ObservationSequence;
template <typename T>
class HighOrderCRFProcessor;

}


namespace Tagger {

using Dictionary::DictionaryClass;
using HighOrderCRF::FeatureTemplateGenerator;
using HighOrderCRF::HighOrderCRFProcessor;
using HighOrderCRF::ObservationSequence;

using std::shared_ptr;
using std::string;
using std::unordered_set;
using std::vector;

class TaggerClass {

public:
    TaggerClass(const TaggerOptions &taggerOptions);
    void train(const string &trainingFilename, const string &modelFilename, shared_ptr<unordered_set<string>> tagSet);
    string tag(const string &line) const;
    void test(const string &testFilename);
    void readModel(const string &modelFilename);

private:
    shared_ptr<vector<shared_ptr<ObservationSequence<string>>>> readData(const string &fileName, bool hasValidLabels);
    shared_ptr<FeatureTemplateGenerator<string>> featureGenerator;
    shared_ptr<DictionaryClass> dictionary;
    shared_ptr<HighOrderCRFProcessor<string>> CRFProcessor;
    TaggerOptions options;
};

}

#endif  // TAGGER_TAGGER_CLASS_H_
