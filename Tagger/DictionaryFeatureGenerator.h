#ifndef HOCRF_TAGGER_DICTIONARY_FEATURE_GENERATOR_H_
#define HOCRF_TAGGER_DICTIONARY_FEATURE_GENERATOR_H_

#include "../Dictionary/DictionaryClass.h"
#include "../HighOrderCRF/FeatureTemplate.h"
#include "../HighOrderCRF/FeatureTemplateGenerator.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Tagger {

using std::map;
using std::shared_ptr;
using std::string;
using std::vector;

using Dictionary::DictionaryClass;
using HighOrderCRF::FeatureTemplate;
using HighOrderCRF::FeatureTemplateGenerator;

class DictionaryFeatureGenerator : public FeatureTemplateGenerator<string> {
public:
    DictionaryFeatureGenerator(shared_ptr<DictionaryClass> dictionary);
    virtual shared_ptr<vector<shared_ptr<FeatureTemplate>>> generateFeatureTemplatesAt(shared_ptr<vector<string>> observationList, size_t pos) const;

private:
    shared_ptr<DictionaryClass> dictionary;
    shared_ptr<map<shared_ptr<vector<string>>, shared_ptr<vector<shared_ptr<vector<shared_ptr<FeatureTemplate>>>>>>> resultCache;
};

}

#endif  // HOCRF_TAGGER_DICTIONARY_FEATURE_GENERATOR_H_
