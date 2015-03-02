#include "CharacterFeatureGenerator.h"

#include "UnicodeCharacter.h"

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>

namespace Segmenter {

using std::make_shared;
using std::max;
using std::min;
using std::shared_ptr;
using std::string;
using std::vector;

CharacterFeatureGenerator::CharacterFeatureGenerator(size_t maxNgram, size_t maxWindow, size_t maxLabelLength) {
    this->maxNgram = maxNgram;
    this->maxWindow = maxWindow;
    this->maxLabelLength = maxLabelLength;
}

shared_ptr<vector<shared_ptr<FeatureTemplate>>> CharacterFeatureGenerator::generateFeatureTemplatesAt(shared_ptr<vector<UnicodeCharacter>> observationList, size_t pos) const {
    int startPos = max(0, (int)pos - (int)maxWindow);
    size_t endPos = min(observationList->size(), pos + maxWindow);
    assert(startPos >= 0);
    auto featureTemplateList = make_shared<vector<shared_ptr<FeatureTemplate>>>();

    for (size_t curPos = startPos; curPos <= pos; ++curPos) {
        size_t maxN = min(endPos - curPos, maxNgram);
        int curPosOffset = curPos - pos + (curPos >= pos ? 1 : 0);
            
        char buffer[256];
        sprintf(buffer, "C%+d/", curPosOffset);
        string prefix(buffer);
        for (size_t n = 1; n <= maxN; ++n) {
#ifdef EMULATE_BOS_EOS
            if (curPos == 0 || pos == observationList->size() - 1 || curPos + n == observationList->size()) {
                continue;
            }
#endif
            if (curPos + n < pos || curPos > pos) {
                continue;
            }
            string obs(prefix);
            for (size_t offset = 0; offset < n; ++offset) {
                obs += observationList->at(curPos + offset).toString();
            }
            size_t maxLen = min(maxLabelLength, pos - curPos + 1);
            for (size_t labelLength = 1; labelLength <= maxLen; ++labelLength) {
                featureTemplateList->push_back(make_shared<FeatureTemplate>(obs, labelLength));
            }
        }
    }
    return featureTemplateList;
}

}  // namespace Segmenter
