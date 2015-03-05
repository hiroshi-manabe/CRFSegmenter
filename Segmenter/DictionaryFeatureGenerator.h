#ifndef SEGMENTER_DICTIONARY_FEATURE_GENERATOR_H_
#define SEGMENTER_DICTIONARY_FEATURE_GENERATOR_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../HighOrderCRF/FeatureTemplate.h"
#include "../HighOrderCRF/FeatureTemplateGenerator.h"
#include "Dictionary.h"

namespace Segmenter {

using std::map;
using std::shared_ptr;
using std::string;
using std::vector;

using HighOrderCRF::FeatureTemplate;
using HighOrderCRF::FeatureTemplateGenerator;

class UnicodeCharacter;

class DictionaryFeatureGenerator : public FeatureTemplateGenerator<UnicodeCharacter> {
public:
    DictionaryFeatureGenerator(const string &dictionaryFile);
    virtual shared_ptr<vector<shared_ptr<FeatureTemplate>>> generateFeatureTemplatesAt(shared_ptr<vector<UnicodeCharacter>> observationList, size_t pos) const;

private:
    shared_ptr<Dictionary> dictionary;
    shared_ptr<map<shared_ptr<vector<UnicodeCharacter>>, shared_ptr<vector<shared_ptr<vector<shared_ptr<FeatureTemplate>>>>>>> resultCache;
};

}

#endif  // SEGMENTER_DICTIONARY_FEATURE_GENERATOR_H_
