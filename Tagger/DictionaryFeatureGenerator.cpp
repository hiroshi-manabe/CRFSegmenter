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

shared_ptr<vector<vector<shared_ptr<FeatureTemplate>>>> DictionaryFeatureGenerator::generateFeatureTemplates(shared_ptr<vector<string>> observationList) const {
    auto templateListList = make_shared<vector<vector<shared_ptr<FeatureTemplate>>>>(observationList->size());

    // Generates all the templates
        
    for (size_t i = 0; i < templateListList->size(); ++i) {
        // Looks up the words
        auto resultListList = dictionary->lookup((*observationList)[i]);
        for (const auto &resultList : resultListList) {
            assert(resultList.size() == 1);
            (*templateListList)[i].push_back(make_shared<FeatureTemplate>(string("D-") + *resultList[0], 1));
        }
    }
    return templateListList;
}

}  // namespace Tagger
