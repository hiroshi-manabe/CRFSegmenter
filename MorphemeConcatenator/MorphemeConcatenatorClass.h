#ifndef MORPHEME_CONCATENATOR_MORPHEME_CONCATENATOR_CLASS_H_
#define MORPHEME_CONCATENATOR_MORPHEME_CONCATENATOR_CLASS_H_

#include "../Dictionary/DictionaryClass.h"

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace MorphemeConcatenator {

class MorphemeConcatenatorClass {

public:
    MorphemeConcatenatorClass(const std::unordered_set<std::string> &dictionaries);
    std::vector<std::vector<std::string>> concatenate(const std::vector<std::vector<std::string>> &sentence) const;

private:
    std::shared_ptr<Dictionary::DictionaryClass> dictionary;
};

}

#endif  // MORPHEME_CONCATENATOR_MORPHEME_CONCATENATOR_CLASS_H_
