#ifndef HOCRF_TAGGER_TAGGER_OPTIONS_H_
#define HOCRF_TAGGER_TAGGER_OPTIONS_H_

#include <string>

namespace Tagger {

using std::string;

struct TaggerOptions {
    size_t wordMaxNgram;
    size_t wordMaxWindow;
    size_t wordMaxLabelLength;
    size_t numThreads;
    double coeff;
    double epsilon;
    size_t maxIter;
    string regType;
    string dictionaryFilename;
};

}

#endif  // HOCRF_TAGGER_TAGGER_OPTIONS_H_
