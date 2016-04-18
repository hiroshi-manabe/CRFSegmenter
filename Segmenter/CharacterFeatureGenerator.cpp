#include "CharacterFeatureGenerator.h"

#include "CharWithSpace.h"

#include <algorithm>
#include <cassert>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace Segmenter {

using std::make_shared;
using std::max;
using std::min;
using std::shared_ptr;
using std::showpos;
using std::string;
using std::stringstream;
using std::vector;

CharacterFeatureGenerator::CharacterFeatureGenerator(size_t maxNgram, size_t maxWindow, size_t maxLabelLength) {
    this->maxNgram = maxNgram;
    this->maxWindow = maxWindow;
    this->maxLabelLength = maxLabelLength;
}

shared_ptr<vector<vector<shared_ptr<FeatureTemplate>>>> CharacterFeatureGenerator::generateFeatureTemplates(shared_ptr<vector<CharWithSpace>> observationList) const {
    auto featureTemplateListList = make_shared<vector<vector<shared_ptr<FeatureTemplate>>>>(observationList->size());
    for (size_t pos = 0; pos < observationList->size(); ++pos) {
        int startPos = max(0, (int)pos - (int)maxWindow);
        size_t endPos = min(observationList->size(), pos + maxWindow);
        assert(startPos >= 0);

        for (size_t curPos = startPos; curPos <= pos; ++curPos) {
            size_t maxN = min(endPos - curPos, maxNgram);
            int curPosOffset = curPos - pos + (curPos >= pos ? 1 : 0);

            stringstream prefix;
            prefix << "C" << showpos << curPosOffset << "/";
            for (size_t n = 1; n <= maxN; ++n) {
                if (curPos + n < pos || curPos > pos) {
                    continue;
                }
                string obs(prefix.str());
                for (size_t offset = 0; offset < n; ++offset) {
                    obs += observationList->at(curPos + offset).toString();
                }
                size_t maxLen = min(maxLabelLength, pos - curPos + 1);
                for (size_t labelLength = 1; labelLength <= maxLen; ++labelLength) {
                    (*featureTemplateListList)[pos].push_back(make_shared<FeatureTemplate>(obs, labelLength));
                }
            }
        }
    }
    return featureTemplateListList;
}

}  // namespace Segmenter
