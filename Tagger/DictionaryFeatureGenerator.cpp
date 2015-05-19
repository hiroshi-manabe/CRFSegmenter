#include "DictionaryFeatureGenerator.h"

#include "../Dictionary/DictionaryClass.h"
#include "../HighOrderCRF/FeatureTemplate.h"

#include <algorithm>
#include <cassert>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace Tagger {

using std::make_shared;
using std::make_pair;
using std::shared_ptr;
using std::string;
using std::vector;

using Dictionary::DictionaryClass;
using HighOrderCRF::FeatureTemplate;

DictionaryFeatureGenerator::DictionaryFeatureGenerator(shared_ptr<DictionaryClass> dictionary) {
    this->dictionary = dictionary;
    resultCache = make_shared<map<shared_ptr<vector<string>>, shared_ptr<vector<shared_ptr<vector<shared_ptr<FeatureTemplate>>>>>>>();
}

shared_ptr<vector<shared_ptr<FeatureTemplate>>> DictionaryFeatureGenerator::generateFeatureTemplatesAt(shared_ptr<vector<string>> observationList, size_t pos) const {
    if (resultCache->find(observationList) == resultCache->end()) {
        auto templateListList = make_shared<vector<shared_ptr<vector<shared_ptr<FeatureTemplate>>>>>(observationList->size());

        // Generates all the templates
        
        for (size_t i = 0; i < templateListList->size(); ++i) {
            // Looks up the words
            auto results = dictionary->lookup((*observationList)[i]);
            for (const auto &s : results) {
                auto &templateList = (*templateListList)[i];
                templateList = make_shared<vector<shared_ptr<FeatureTemplate>>>();
                templateList->push_back(make_shared<FeatureTemplate>(string("D-") + s, 1));
            }
        }
        resultCache->insert(make_pair(observationList, templateListList));
    }
    const auto it = *resultCache->find(observationList);
    const auto cachedTemplateListList = it.second;
    if ((*cachedTemplateListList)[pos]) {
        return (*cachedTemplateListList)[pos];
    } else {
        return make_shared<vector<shared_ptr<FeatureTemplate>>>();
    }
}

}  // namespace Tagger
