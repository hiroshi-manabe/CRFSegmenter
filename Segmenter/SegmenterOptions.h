#ifndef SEGMENTER_TRAINING_OPTIONS_H_
#define SEGMENTER_TRAINING_OPTIONS_H_

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
    size_t numThreads;
    string dictionaryFilename;
};

}

#endif  // SEGMENTER_TRAINING_OPTIONS_H_
