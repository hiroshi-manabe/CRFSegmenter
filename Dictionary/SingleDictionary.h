#ifndef HOCRF_DICTIONARY_SINGLE_DICTIONARY_H_
#define HOCRF_DICTIONARY_SINGLE_DICTIONARY_H_

#include <cstdint>
#include <cstdlib>
#include <functional>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "../libmarisa/marisa.h"

namespace Dictionary {

class SingleDictionary {
public:
    SingleDictionary(const std::string &file, std::function<void(char *, size_t)> decrypt = nullptr);
    static void build(std::istream &is, std::ostream &os, std::function<void(char *, size_t)> encrypt = nullptr);
    std::vector<std::pair<size_t, std::vector<std::vector<std::string>>>> commonPrefixSearch(const std::string &str) const;
    std::vector<std::vector<std::string>> lookup(const std::string &str) const;

private:
    std::vector<std::vector<std::string>> getLines(size_t entryId) const;
    marisa::Trie entryTrie;
    marisa::Trie fieldTrie;
    uint32_t numberOfFieldsPerLine;
    std::vector<uint32_t> lastLineIndexList;
    std::vector<uint32_t> fieldIdList;
};

}  // namespace Dictionary

#endif  // HOCRF_DICTIONARY_SINGLE_DICTIONARY_H_
