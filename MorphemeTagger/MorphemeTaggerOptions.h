#ifndef HOCRF_MORPHEME_TAGGER_MORPHEME_TAGGER_OPTIONS_H_
#define HOCRF_MORPHEME_TAGGER_MORPHEME_TAGGER_OPTIONS_H_

#include <string>
#include <unordered_set>

namespace MorphemeTagger {

using std::string;
using std::unordered_set;

struct MorphemeTaggerOptions {
    size_t wordMaxWindow;
    size_t labelMaxWindow;
    size_t columnMaxWindow;
    size_t numThreads;
    double coeff;
    double epsilon;
    size_t maxIter;
    string regType;
    unordered_set<size_t> featureColumnSet;
    string dictionaryFilename;
};

}

#endif  // HOCRF_MORPHEME_TAGGER_MORPHEME_TAGGER_OPTIONS_H_
