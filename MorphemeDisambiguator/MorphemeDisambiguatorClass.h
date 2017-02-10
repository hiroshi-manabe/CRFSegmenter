#ifndef MORPHEME_DISAMBIGUATOR_MORPHEME_DISAMBIGUATOR_CLASS_H_
#define MORPHEME_DISAMBIGUATOR_MORPHEME_DISAMBIGUATOR_CLASS_H_

#include "../Dictionary/DictionaryClass.h"
#include "MorphemeDisambiguatorOptions.h"

#include <memory>
#include <string>
#include <vector>

namespace MaxEnt {
class MaxEntProcessor;
}

namespace MorphemeDisambiguator {

class MorphemeDisambiguatorClass {

public:
    MorphemeDisambiguatorClass(const MorphemeDisambiguatorOptions &taggerOptions);
    void train(const std::string &trainingFilename,
               size_t concurrency,
               size_t maxIter,
               double regularizationCoefficientL1,
               double regularizationCoefficientL2,
               double epsilonForConvergence,
               const std::string &modelFilename);
    std::vector<std::vector<std::string>> tag(std::vector<std::string> sentence) const;
    void test(const std::string &testFilename) const;
    void readModel(const std::string &modelFilename);

private:
    std::shared_ptr<Dictionary::DictionaryClass> dictionary;
    std::shared_ptr<MaxEnt::MaxEntProcessor> maxEntProcessor;
    MorphemeDisambiguatorOptions options;
};

}

#endif  // MORPHEME_DISAMBIGUATOR_MORPHEME_DISAMBIGUATOR_CLASS_H_
