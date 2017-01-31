#ifndef HOCRF_DICTIONARY_DICTIONARY_CLASS_H_
#define HOCRF_DICTIONARY_DICTIONARY_CLASS_H_

#include <cstdlib>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "../libmarisa/marisa.h"

namespace Dictionary {

class DictionaryClass {
public:
    DictionaryClass(const std::unordered_set<std::string> &files);
    std::vector<std::pair<size_t, std::vector<std::vector<const std::string *>>>> commonPrefixSearch(const std::string &str) const;
    std::vector<std::vector<const std::string *>> lookup(const std::string &str) const;

private:
    std::vector<std::vector<std::vector<size_t>>> marisaIdToFeatureIdListListList;
    std::vector<std::string> featureIdToStringList;
    marisa::Trie trie;
};

}  // namespace Dictionary

#endif  // HOCRF_DICTIONARY_DICTIONARY_CLASS_H_
