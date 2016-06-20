#ifndef HOCRF_SEGMENTER_SEGMENTER_OPTIONS_H_
#define HOCRF_SEGMENTER_SEGMENTER_OPTIONS_H_

#include <string>

namespace Segmenter {

using std::string;

struct SegmenterOptions {
    size_t charMaxNgram;
    size_t charMaxWindow;
    size_t charMaxLabelLength;
    size_t charTypeMaxNgram;
    size_t charTypeMaxWindow;
    size_t charTypeMaxLabelLength;
    size_t wordMaxLabelLength;
    size_t numThreads;
    double coeff;
    double epsilon;
    size_t maxIter;
    string regType;
    string dictionaryFilename;
    bool hasLabels;
    bool concatenate;
    bool ignoreLatin;
    bool asciiSpaceOnly;
    bool containsSpaces;
};

}

#endif  // HOCRF_SEGMENTER_SEGMENTER_OPTIONS_H_
