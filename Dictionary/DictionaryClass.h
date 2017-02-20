#ifndef HOCRF_DICTIONARY_DICTIONARY_CLASS_H_
#define HOCRF_DICTIONARY_DICTIONARY_CLASS_H_

#include "SingleDictionary.h"

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Dictionary {

class SingleDictionary;

class DictionaryClass {
public:
    DictionaryClass(const std::unordered_set<std::string> &files, void (*decode)(char *, size_t) = nullptr);
    std::vector<std::pair<size_t, std::vector<std::vector<std::string>>>> commonPrefixSearch(const std::string &str) const;
    std::vector<std::vector<std::string>> lookup(const std::string &str) const;

private:
    std::vector<std::shared_ptr<SingleDictionary>> dictionaryList;
};

}  // namespace Dictionary

#endif  // HOCRF_DICTIONARY_DICTIONARY_CLASS_H_
