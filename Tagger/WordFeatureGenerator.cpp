#include "WordFeatureGenerator.h"

#include <algorithm>
#include <cassert>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace Tagger {

using std::make_shared;
using std::max;
using std::min;
using std::shared_ptr;
using std::showpos;
using std::string;
using std::stringstream;
using std::vector;

WordFeatureGenerator::WordFeatureGenerator(size_t maxNgram, size_t maxWindow, size_t maxLabelLength) {
    this->maxNgram = maxNgram;
    this->maxWindow = maxWindow;
    this->maxLabelLength = maxLabelLength;
}

shared_ptr<vector<shared_ptr<FeatureTemplate>>> WordFeatureGenerator::generateFeatureTemplatesAt(shared_ptr<vector<string>> observationList, size_t pos) const {
    int startPos = max(0, (int)pos - (int)maxWindow);
    size_t endPos = min(observationList->size(), pos + maxWindow);
    assert(startPos >= 0);
    auto featureTemplateList = make_shared<vector<shared_ptr<FeatureTemplate>>>();

    for (size_t curPos = startPos; curPos <= pos; ++curPos) {
        size_t maxN = min(endPos - curPos, maxNgram);
        int curPosOffset = curPos - pos;

        stringstream prefix;
        prefix << "W" << showpos << curPosOffset << "/";
        for (size_t n = 1; n <= maxN; ++n) {
            if (curPos + n < pos || curPos > pos) {
                continue;
            }
            string obs(prefix.str());
            for (size_t offset = 0; offset < n; ++offset) {
                obs += observationList->at(curPos + offset);
                if (offset < n - 1) {
                    obs += "_";
                }
            }
            size_t maxLen = min(maxLabelLength, pos - curPos + 2);
            for (size_t labelLength = 1; labelLength <= maxLen; ++labelLength) {
                featureTemplateList->push_back(make_shared<FeatureTemplate>(obs, labelLength));
            }
        }
    }
    return featureTemplateList;
}

}  // namespace Tagger