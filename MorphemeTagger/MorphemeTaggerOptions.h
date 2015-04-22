#ifndef HOCRF_MORPHEME_TAGGER_MORPHEME_TAGGER_OPTIONS_H_
#define HOCRF_MORPHEME_TAGGER_MORPHEME_TAGGER_OPTIONS_H_

#include <string>

namespace MorphemeTagger {

using std::string;

struct MorphemeTaggerOptions {
    size_t maxBagOffset;
    size_t maxWordOffset;
    size_t maxLabelOffset;
    size_t numThreads;
    string dictionaryFilename;
};

}

#endif  // HOCRF_MORPHEME_TAGGER_MORPHEME_TAGGER_OPTIONS_H_
