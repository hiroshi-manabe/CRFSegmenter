#include "SegmenterDictionaryFeatureGenerator.h"

#include "../Dictionary/DictionaryClass.h"
#include "../Utility/CharWithSpace.h"

#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace DataConverter {

using std::make_shared;
using std::move;
using std::string;
using std::unordered_set;
using std::vector;

using Dictionary::DictionaryClass;
using HighOrderCRF::FeatureTemplate;
using Utility::CharWithSpace;

SegmenterDictionaryFeatureGenerator::SegmenterDictionaryFeatureGenerator(const unordered_set<string> &dictionaries, size_t maxLabelLength) {
    dictionary = make_shared<DictionaryClass>(dictionaries);
    this->maxLabelLength = maxLabelLength;
}

vector<vector<FeatureTemplate>> SegmenterDictionaryFeatureGenerator::generateFeatureTemplates(const vector<CharWithSpace> &observationList) const {
    vector<vector<FeatureTemplate>> featureTemplateListList(observationList.size());

    // Generates all the templates
        
    // Reconstructs the whole sentence, recording the start positions
    string sentence;
    vector<size_t> startPosList;
        
    for (const auto uchar : observationList) {
        startPosList.emplace_back(sentence.length());
        sentence += uchar.toString();
    }
    startPosList.emplace_back(sentence.length());

    vector<size_t> utf8PosToCharPosList(sentence.length() + 1);
    for (size_t i = 0; i < startPosList.size(); ++i) {
        utf8PosToCharPosList[startPosList[i]] = i;
    }
    utf8PosToCharPosList[sentence.length()] = startPosList.size();

    for (size_t i = 0; i < startPosList.size() - 1; ++i) {
        size_t startUtf8Pos = startPosList[i];
        auto ch = observationList[i];
        // skip the space if there is one
        if (ch.hasSpace()) {
            ++startUtf8Pos;
        }
        // Looks up the words
        auto results = dictionary->commonPrefixSearch(
            string(sentence.c_str() + startUtf8Pos, sentence.length() - startUtf8Pos));
        for (auto &p : results) {
            auto charLength = p.first;
            auto &featureListList = p.second;
            unordered_set<string> featureSet;
            for (auto &featureList : featureListList) {
                for (auto &feature : featureList) {
                    featureSet.emplace(move(feature));
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
            bool hasRightSpace = (endCharPos < observationList.size() ? observationList[endCharPos].hasSpace() : true);
            string spaceStr;
            if (hasLeftSpace) {
                spaceStr += "LS";
            }
            if (hasRightSpace) {
                spaceStr += "RS";
            }
            spaceStr += "-";

            // Feature template for the left position
            auto &leftTemplateList = featureTemplateListList[i];
            for (const auto &featureStr : featureSet) {
                leftTemplateList.emplace_back(string("Rw-") + featureStr, 1);
                if (hasLeftSpace || hasRightSpace) {
                    leftTemplateList.emplace_back(string("Rw") + spaceStr + featureStr, 1);
                }
            }

            if (endCharPos >= observationList.size()) {
                continue;
            }
            // Feature templates for the right position
            auto &rightTemplateList = featureTemplateListList[endCharPos];
            for (const auto &featureStr : featureSet) {
                rightTemplateList.emplace_back(string("Lw-") + featureStr, 1);
                rightTemplateList.emplace_back(string("LW-") + featureStr, labelLength);
                if (hasLeftSpace || hasRightSpace) {
                    rightTemplateList.emplace_back(string("Lw") + spaceStr + featureStr, 1);
                    rightTemplateList.emplace_back(string("LW") + spaceStr + featureStr, labelLength);
                }
            }
        }
    }
    return featureTemplateListList;
}

}  // namespace DataConverter
