#include <algorithm>
#include <cassert>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "WordCharacterFeatureGenerator.h"

#include "UnicodeCharacter.h"

namespace DataConverter {

using std::make_shared;
using std::shared_ptr;
using std::showpos;
using std::string;
using std::stringstream;
using std::unordered_set;
using std::vector;

using HighOrderCRF::FeatureTemplate;

WordCharacterFeatureGenerator::WordCharacterFeatureGenerator(size_t maxLength) {
    this->maxLength = maxLength;
}

static string utf8Substr(const string &str, size_t len, bool fromTail) {
    vector<UnicodeCharacter> unicodeList;
    for (auto it = str.begin(); it != str.end(); ) {
        size_t charCount;
        unicodeList.push_back(UnicodeCharacter::fromString(it, str.end() - it, &charCount));
        it += charCount;
    }
    if (len > unicodeList.size()) {
        return "";
    }
    stringstream ss;
    for (size_t i = 0; i < len; ++i) {
        ss << unicodeList[fromTail ? unicodeList.size() - len + i : i].toString();
    }
    return ss.str();
}

vector<vector<FeatureTemplate>> WordCharacterFeatureGenerator::generateFeatureTemplates(const vector<string> &observationList) const {
    vector<vector<FeatureTemplate>> featureTemplateListList;
    featureTemplateListList.reserve(observationList.size());
    for (size_t pos = 0; pos < observationList.size(); ++pos) {
        vector<FeatureTemplate> featureTemplateList;
        bool ft[] = { false, true };
        size_t wordLen = observationList[pos].size();
        unordered_set<size_t> usedPosSet;
        for (auto fromTail : ft) {
            for (size_t len = 1; len <= maxLength; ++len) {
                string str = utf8Substr(observationList[pos], len, fromTail);
                if (!str.empty()) {
                    stringstream ss;
                    ss << "C" << (fromTail ? "-" : "+") << len << "/" << str;
                    featureTemplateList.emplace_back(ss.str(), 1);
                }
            }
        }
        featureTemplateListList.emplace_back(move(featureTemplateList));
    }
    return featureTemplateListList;
}

}  // namespace DataConverter
