#include "DictionaryFeatureGenerator.h"

#include "UnicodeCharacter.h"

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace Segmenter {

using std::make_shared;
using std::make_pair;
using std::max;
using std::min;
using std::shared_ptr;
using std::string;
using std::vector;

DictionaryFeatureGenerator::DictionaryFeatureGenerator(const string &dictionaryFile) {
    dictionary = make_shared<marisa::Trie>();
    dictionary->load(dictionaryFile.c_str());
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

        // Looks up the words
        marisa::Agent agent;
        for (size_t i = 0; i < startPosList.size(); ++i) {
            size_t startUtf8Pos = startPosList[i];
            agent.set_query(sentence.c_str() + startUtf8Pos, sentence.length() - startUtf8Pos);
            while (dictionary->common_prefix_search(agent)) {
                size_t endCharPos = utf8PosToCharPosList[startUtf8Pos + agent.key().length()];
                if (endCharPos == 0) {  // This cannot happen if everything is in well-formed utf-8
                    continue;
                }
                int wordLength = endCharPos - i;
                assert(wordLength > 0);
                string word(sentence.c_str() + startUtf8Pos, agent.key().length());

                char buffer[256];
                sprintf(buffer, "%d", wordLength);
                string wordLengthStr(buffer);
                size_t labelLength = wordLength + 1;
                if (labelLength > 5) {
                    labelLength = 5;
                }
                sprintf(buffer, "%d", labelLength);
                string labelLengthStr(buffer);

                // Feature template for the left position
                auto &leftTemplateList = (*templateListList)[i];
                if (!leftTemplateList) {
                    leftTemplateList = make_shared<vector<shared_ptr<FeatureTemplate>>>();
                }
                string rightObs("RW0/");
                rightObs += word;
//                leftTemplateList->push_back(make_shared<FeatureTemplate>(rightObs, 1));
                leftTemplateList->push_back(make_shared<FeatureTemplate>(string("Rw") + wordLengthStr + "-1", 1));

                if (endCharPos >= observationList->size()) {
                    continue;
                }
                // Feature templates for the right position
                auto &rightTemplateList = (*templateListList)[endCharPos];
                if (!rightTemplateList) {
                    rightTemplateList = make_shared<vector<shared_ptr<FeatureTemplate>>>();
                }
                string leftObs("LW0/");
                leftObs += word;
//                rightTemplateList->push_back(make_shared<FeatureTemplate>(leftObs, 1));
                rightTemplateList->push_back(make_shared<FeatureTemplate>(string("Lw") + wordLengthStr + "-1", 1));

                string leftObs2("LW");
                leftObs2 += buffer;
                leftObs2 += "/";
                leftObs2.append(sentence.c_str() + startUtf8Pos, agent.key().length());
//                rightTemplateList->push_back(make_shared<FeatureTemplate>(leftObs2, wordLength + 1));
                rightTemplateList->push_back(make_shared<FeatureTemplate>(string("Lw") + wordLengthStr + "-" + labelLengthStr, labelLength));
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
