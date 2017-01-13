#include <algorithm>
#include <cassert>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "WordCharacterTypeFeatureGenerator.h"

#include "UnicodeCharacter.h"

namespace DataConverter {

using std::string;
using std::stringstream;
using std::unordered_set;
using std::vector;

using HighOrderCRF::FeatureTemplate;

WordCharacterTypeFeatureGenerator::WordCharacterTypeFeatureGenerator(size_t maxLength) {
    this->maxLength = maxLength;
}

static string utf8SubstrToCharacterTypeString(const string &str, size_t len, bool fromTail) {
    vector<UnicodeCharacter> unicodeList;
    for (auto it = str.begin(); it != str.end(); ) {
        size_t charCount;
        unicodeList.push_back(UnicodeCharacter::fromString(it, str.end() - it, &charCount));
        it += charCount;
    }
    if (len > unicodeList.size()) {
        return "";
    }
    bool isFirst = true;
    stringstream ss;
    for (size_t i = 0; i < len; ++i) {
        if (!isFirst) {
            ss << "_";
        }
        ss << unicodeList[fromTail ? unicodeList.size() - len + i : i].getCharacterType();
        isFirst = false;
    }
    return ss.str();
}

vector<vector<FeatureTemplate>> WordCharacterTypeFeatureGenerator::generateFeatureTemplates(const vector<string> &observationList) const {
    vector<vector<FeatureTemplate>> featureTemplateListList;
    featureTemplateListList.reserve(observationList.size());
    for (size_t pos = 0; pos < observationList.size(); ++pos) {
        vector<FeatureTemplate> featureTemplateList;
        bool ft[] = { false, true };
        size_t wordLen = observationList[pos].size();
        unordered_set<size_t> usedPosSet;
        for (auto fromTail : ft) {
            for (size_t len = 1; len <= maxLength; ++len) {
                string str = utf8SubstrToCharacterTypeString(observationList[pos], len, fromTail);
                if (!str.empty()) {
                    stringstream ss;
                    ss << "T" << (fromTail ? "-" : "+") << len << "/" << str;
                    featureTemplateList.emplace_back(ss.str(), 1);
                }
            }
        }
        featureTemplateListList.emplace_back(move(featureTemplateList));
    }
    return featureTemplateListList;
}

}  // namespace DataConverter
