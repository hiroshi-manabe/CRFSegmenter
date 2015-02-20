#ifndef SEGMENTER_TRAINING_OPTIONS_H_
#define SEGMENTER_TRAINING_OPTIONS_H_

#include <string>

namespace Segmenter {

struct TrainingOptions {
    size_t charMaxNgram;
    size_t charMaxWindow;
    size_t charMaxLabelLength;
    size_t charTypeMaxNgram;
    size_t charTypeMaxWindow;
    size_t charTypeMaxLabelLength;
};

}

#endif  // SEGMENTER_TRAINING_OPTIONS_H_
