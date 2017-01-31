#ifndef HOCRF_MORPHEME_TAGGER_MORPHEME_TAGGER_OPTIONS_H_
#define HOCRF_MORPHEME_TAGGER_MORPHEME_TAGGER_OPTIONS_H_

#include <string>
#include <unordered_set>

namespace MorphemeDisambiguator {

struct MorphemeDisambiguatorOptions {
    size_t wordMaxWindow;
    size_t labelMaxWindow;
    size_t columnMaxWindow;
    std::unordered_set<size_t> featureColumnSet;
    std::unordered_set<std::string> dictionaries;
};

}

#endif  // HOCRF_MORPHEME_TAGGER_MORPHEME_TAGGER_OPTIONS_H_
