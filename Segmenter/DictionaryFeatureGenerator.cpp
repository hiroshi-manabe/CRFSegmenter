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

DictionaryFeatureGenerator::DictionaryFeatureGenerator(const string &dictionaryFile, size_t maxLabelLength) {
    dictionary = make_shared<DictionaryClass>(dictionaryFile);
    resultCache = make_shared<unordered_map<shared_ptr<vector<CharWithSpace>>, shared_ptr<vector<shared_ptr<vector<shared_ptr<FeatureTemplate>>>>>>>();
    this->maxLabelLength = maxLabelLength;
}

shared_ptr<vector<vector<shared_ptr<FeatureTemplate>>>> DictionaryFeatureGenerator::generateFeatureTemplates(shared_ptr<vector<CharWithSpace>> observationList) const {
    auto templateListList = make_shared<vector<vector<shared_ptr<FeatureTemplate>>>>(observationList->size());

    // Generates all the templates
        
    // Reconstructs the whole sentence, recording the start positions
    string sentence;
    vector<size_t> startPosList;
        
    for (auto uchar : *observationList) {
        startPosList.push_back(sentence.length());
        sentence += uchar.toString();
    }
    startPosList.push_back(sentence.length());

    vector<size_t> utf8PosToCharPosList(sentence.length() + 1);
    for (size_t i = 0; i < startPosList.size(); ++i) {
        utf8PosToCharPosList[startPosList[i]] = i;
    }
    utf8PosToCharPosList[sentence.length()] = startPosList.size();

    for (size_t i = 0; i < startPosList.size() - 1; ++i) {
        size_t startUtf8Pos = startPosList[i];
        auto ch = observationList->at(i);
        // skip the space if there is one
        if (ch.hasSpace()) {
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
            if (labelLength > maxLabelLength) {
                labelLength = maxLabelLength;
            }
            bool hasLeftSpace = ch.hasSpace();
            bool hasRightSpace = (endCharPos < observationList->size() ? observationList->at(endCharPos).hasSpace() : true);
            string spaceStr;
            if (hasLeftSpace) {
                spaceStr += "LS";
            }
            if (hasRightSpace) {
                spaceStr += "RS";
            }
            spaceStr += "-";

            // Feature template for the left position
            auto &leftTemplateList = (*templateListList)[i];
            for (const auto &featureStr : featureSet) {
                leftTemplateList.push_back(make_shared<FeatureTemplate>(string("Rw-") + *featureStr, 1));
                if (hasLeftSpace || hasRightSpace) {
                    leftTemplateList.push_back(make_shared<FeatureTemplate>(string("Rw") + spaceStr + *featureStr, 1));
                }
            }

            if (endCharPos >= observationList->size()) {
                continue;
            }
            // Feature templates for the right position
            auto &rightTemplateList = (*templateListList)[endCharPos];
            for (const auto &featureStr : featureSet) {
                rightTemplateList.push_back(make_shared<FeatureTemplate>(string("Lw-") + *featureStr, 1));
                rightTemplateList.push_back(make_shared<FeatureTemplate>(string("LW-") + *featureStr, labelLength));
                if (hasLeftSpace || hasRightSpace) {
                    rightTemplateList.push_back(make_shared<FeatureTemplate>(string("Lw") + spaceStr + *featureStr, 1));
                    rightTemplateList.push_back(make_shared<FeatureTemplate>(string("LW") + spaceStr + *featureStr, labelLength));
                }
            }
        }
    }
    return templateListList;
}

}  // namespace Segmenter
