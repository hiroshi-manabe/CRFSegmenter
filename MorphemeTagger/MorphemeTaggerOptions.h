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
    unordered_set<size_t> featureColumnSet;
    size_t numThreads;
    string dictionaryFilename;
};

}

#endif  // HOCRF_MORPHEME_TAGGER_MORPHEME_TAGGER_OPTIONS_H_
