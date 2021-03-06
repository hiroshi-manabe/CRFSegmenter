#ifndef HOCRF_DICTIONARY_DICTIONARY_CLASS_H_
#define HOCRF_DICTIONARY_DICTIONARY_CLASS_H_

#include "SingleDictionary.h"

#include <memory>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Dictionary {

class SingleDictionary;

class DictionaryClass {
public:
    DictionaryClass(const std::unordered_set<std::string> &files);
    std::vector<std::pair<size_t, std::set<std::vector<std::string>>>> commonPrefixSearch(const std::string &str) const;
    std::set<std::vector<std::string>> lookup(const std::string &str) const;

private:
    std::vector<std::shared_ptr<SingleDictionary>> dictionaryList;
};

}  // namespace Dictionary

#endif  // HOCRF_DICTIONARY_DICTIONARY_CLASS_H_
