#include "DictionaryFeatureGenerator.h"

#include "../Dictionary/DictionaryClass.h"
#include "CharWithSpace.h"

#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace Segmenter {

using std::make_shared;
using std::make_pair;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using Dictionary::DictionaryClass;
using HighOrderCRF::FeatureTemplate;

DictionaryFeatureGenerator::DictionaryFeatureGenerator(const string &dictionaryFile) {
    dictionary = make_shared<DictionaryClass>(dictionaryFile);
    resultCache = make_shared<unordered_map<shared_ptr<vector<CharWithSpace>>, shared_ptr<vector<shared_ptr<vector<shared_ptr<FeatureTemplate>>>>>>>();
}

shared_ptr<vector<vector<shared_ptr<FeatureTemplate>>>> DictionaryFeatureGenerator::generateFeatureTemplates(shared_ptr<vector<CharWithSpace>> observationList) const {
    auto templateListList = make_shared<vector<vector<shared_ptr<FeatureTemplate>>>>(observationList->size());

    // Generates all the templates
        
    // Reconstructs the whole sentence, recording the start positions
    string sentence;
    vector<size_t> startPosList;
    // The maximum length of a UTF-8 char is 4
    vector<size_t> utf8PosToCharPosList(observationList->size() * 4 + 1);
        
    for (auto uchar : *observationList) {
        utf8PosToCharPosList[sentence.length()] = startPosList.size();
        startPosList.push_back(sentence.length());
        sentence += uchar.toString();
    }
    utf8PosToCharPosList[sentence.length()] = startPosList.size();
    startPosList.push_back(sentence.length());

    for (size_t i = 0; i < startPosList.size(); ++i) {
        utf8PosToCharPosList[startPosList[i]] = i;
    }

    for (size_t i = 0; i < startPosList.size(); ++i) {
        size_t startUtf8Pos = startPosList[i];
        // skip the space if there is one
        if (observationList->at(i).hasSpace()) {
            ++startUtf8Pos;
        }
        // Looks up the words
        auto results = dictionary->commonPrefixSearch(
            string(sentence.c_str() + startUtf8Pos, sentence.length() - startUtf8Pos));
        for (const auto &p : results) {
            const auto &charLength = p.first;
            const auto &featureListList = p.second;
            unordered_set<const string *> featureSet;
            for (const auto &featureList : featureListList) {
                for (const auto &feature : featureList) {
                    featureSet.insert(feature);
                }
            }
                
            size_t endCharPos = utf8PosToCharPosList[startUtf8Pos + charLength];
            if (endCharPos == 0) {  // This cannot happen if everything is in well-formed utf-8
                continue;
            }
            int wordLength = endCharPos - i;
            assert(wordLength > 0);

            size_t labelLength = wordLength + 1;
            if (labelLength > 5) {
                labelLength = 5;
            }

            // Feature template for the left position
            auto &leftTemplateList = (*templateListList)[i];
            for (const auto &featureStr : featureSet) {
                leftTemplateList.push_back(make_shared<FeatureTemplate>(string("Rw-") + *featureStr, 1));
            }

            if (endCharPos >= observationList->size()) {
                continue;
            }
            // Feature templates for the right position
            auto &rightTemplateList = (*templateListList)[endCharPos];
            for (const auto &featureStr : featureSet) {
                rightTemplateList.push_back(make_shared<FeatureTemplate>(string("Lw-") + *featureStr, 1));
                rightTemplateList.push_back(make_shared<FeatureTemplate>(string("LW-") + *featureStr, labelLength));
            }
        }
    }
    return templateListList;
}

}  // namespace Segmenter
