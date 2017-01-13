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

namespace DataConverter {

using std::shared_ptr;
using std::string;
using std::vector;

using Dictionary::DictionaryClass;
using HighOrderCRF::FeatureTemplate;

DictionaryFeatureGenerator::DictionaryFeatureGenerator(shared_ptr<DictionaryClass> dict) {
    dictionary = dict;
}

vector<vector<FeatureTemplate>> DictionaryFeatureGenerator::generateFeatureTemplates(const vector<string> &observationList) const {
    vector<vector<FeatureTemplate>> featureTemplateListList(observationList.size());

    // Generates all the templates
    for (size_t i = 0; i < featureTemplateListList.size(); ++i) {
        // Looks up the words
        auto resultListList = dictionary->lookup(observationList[i]);
        for (const auto &resultList : resultListList) {
            assert(resultList.size() == 1);
            featureTemplateListList[i].emplace_back(string("D-") + *resultList[0], 1);
        }
    }
    return featureTemplateListList;
}

}  // namespace DataConverter
