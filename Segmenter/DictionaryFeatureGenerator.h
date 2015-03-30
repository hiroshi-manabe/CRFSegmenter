#ifndef HOCRF_SEGMENTER_DICTIONARY_FEATURE_GENERATOR_H_
#define HOCRF_SEGMENTER_DICTIONARY_FEATURE_GENERATOR_H_

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../Dictionary/DictionaryClass.h"
#include "../HighOrderCRF/FeatureTemplate.h"
#include "../HighOrderCRF/FeatureTemplateGenerator.h"

namespace Segmenter {

using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

using Dictionary::DictionaryClass;
using HighOrderCRF::FeatureTemplate;
using HighOrderCRF::FeatureTemplateGenerator;

class UnicodeCharacter;

class DictionaryFeatureGenerator : public FeatureTemplateGenerator<UnicodeCharacter> {
public:
    DictionaryFeatureGenerator(const string &dictionaryFile);
    virtual shared_ptr<vector<shared_ptr<FeatureTemplate>>> generateFeatureTemplatesAt(shared_ptr<vector<UnicodeCharacter>> observationList, size_t pos) const;

private:
    shared_ptr<DictionaryClass> dictionary;
    shared_ptr<unordered_map<shared_ptr<vector<UnicodeCharacter>>, shared_ptr<vector<shared_ptr<vector<shared_ptr<FeatureTemplate>>>>>>> resultCache;
};

}

#endif  // HOCRF_SEGMENTER_DICTIONARY_FEATURE_GENERATOR_H_
