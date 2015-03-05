#include "DictionaryFeatureGenerator.h"

#include "UnicodeCharacter.h"

#include <algorithm>
#include <cassert>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace Segmenter {

using std::make_shared;
using std::make_pair;
using std::max;
using std::min;
using std::pair;
using std::shared_ptr;
using std::string;
using std::stringstream;
using std::vector;

DictionaryFeatureGenerator::DictionaryFeatureGenerator(const string &dictionaryFile) {
    dictionary = make_shared<Dictionary>(dictionaryFile);
    resultCache = make_shared<map<shared_ptr<vector<UnicodeCharacter>>, shared_ptr<vector<shared_ptr<vector<shared_ptr<FeatureTemplate>>>>>>>();
}

shared_ptr<vector<shared_ptr<FeatureTemplate>>> DictionaryFeatureGenerator::generateFeatureTemplatesAt(shared_ptr<vector<UnicodeCharacter>> observationList, size_t pos) const {
    if (resultCache->find(observationList) == resultCache->end()) {
        auto templateListList = make_shared<vector<shared_ptr<vector<shared_ptr<FeatureTemplate>>>>>(observationList->size());

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

        for (size_t i = 0; i < startPosList.size(); ++i) {
            size_t startUtf8Pos = startPosList[i];
            // Looks up the words
            auto results = dictionary->lookup(string(sentence.c_str() + startUtf8Pos, sentence.length() - startUtf8Pos));
            for (const auto &p : results) {
                const auto &charLength = p.first;
                const auto &featureList = p.second;
                
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
                if (!leftTemplateList) {
                    leftTemplateList = make_shared<vector<shared_ptr<FeatureTemplate>>>();
                }
                for (const auto &featureStr : featureList) {
                    leftTemplateList->push_back(make_shared<FeatureTemplate>(string("Rw-") + featureStr, 1));
                }

                if (endCharPos >= observationList->size()) {
                    continue;
                }
                // Feature templates for the right position
                auto &rightTemplateList = (*templateListList)[endCharPos];
                if (!rightTemplateList) {
                    rightTemplateList = make_shared<vector<shared_ptr<FeatureTemplate>>>();
                }
                for (const auto &featureStr : featureList) {
                    rightTemplateList->push_back(make_shared<FeatureTemplate>(string("Lw-") + featureStr, 1));
                    rightTemplateList->push_back(make_shared<FeatureTemplate>(string("LW-") + featureStr, labelLength));
                }
            }
        }
        resultCache->insert(make_pair(observationList, templateListList));
    }
    const auto it = *resultCache->find(observationList);
    const auto cachedTemplateListList = it.second;
#ifdef EMULATE_BOS_EOS
    if (pos == 0 || pos == observationList->size() - 1) {
        return make_shared<vector<shared_ptr<FeatureTemplate>>>();
    }
#endif
    if ((*cachedTemplateListList)[pos]) {
        return (*cachedTemplateListList)[pos];
    } else {
        return make_shared<vector<shared_ptr<FeatureTemplate>>>();
    }
}

}  // namespace Segmenter
