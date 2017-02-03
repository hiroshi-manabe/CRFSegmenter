#include <algorithm>
#include <cassert>
#include <sstream>
#include <string>
#include <vector>

#include "CharWithSpaceTypeFeatureGenerator.h"
#include "CharWithSpace.h"

namespace DataConverter {

using std::max;
using std::min;
using std::showpos;
using std::string;
using std::stringstream;
using std::vector;

using HighOrderCRF::FeatureTemplate;

CharWithSpaceTypeFeatureGenerator::CharWithSpaceTypeFeatureGenerator(size_t maxNgram, size_t maxWindow, size_t maxLabelLength) {
    this->maxNgram = maxNgram;
    this->maxWindow = maxWindow;
    this->maxLabelLength = maxLabelLength;
}

vector<vector<FeatureTemplate>> CharWithSpaceTypeFeatureGenerator::generateFeatureTemplates(const vector<CharWithSpace> &observationList) const {
    vector<vector<FeatureTemplate>> featureTemplateListList(observationList.size());
    for (size_t pos = 0; pos < observationList.size(); ++pos) {
        int startPos = max(0, (int)pos - (int)maxWindow);
        size_t endPos = min(observationList.size(), pos + maxWindow);
        assert(startPos >= 0);

        for (size_t curPos = startPos; curPos <= pos; ++curPos) {
            size_t maxN = min(endPos - curPos, maxNgram);
            int curPosOffset = curPos - pos + (curPos >= pos ? 1 : 0);
        
            stringstream prefix;
            prefix << "TS" << showpos << curPosOffset << "/";
            for (size_t n = 1; n <= maxN; ++n) {
                if (curPos + n < pos || curPos > pos) {
                    continue;
                }
                string obs(prefix.str());
                for (size_t offset = 0; offset < n; ++offset) {
                    auto &cs = observationList[curPos + offset];
                    if (cs.hasSpace()) {
                        obs += "SPACE_";
                    }
                    obs += cs.getUnicodeCharacter().getCharacterType();
                    if (offset < n - 1) {
                        obs += "_";
                    }
                }
                size_t maxLen = min(maxLabelLength, pos - curPos + 1);
                for (size_t labelLength = 1; labelLength <= maxLen; ++labelLength) {
                    featureTemplateListList[pos].emplace_back(obs, labelLength);
                }
            }
        }
    }
    return featureTemplateListList;
}

}  // namespace DataConverter
