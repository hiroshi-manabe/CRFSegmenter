#ifndef HOCRF_DICTIONARY_DICTIONARY_CLASS_H_
#define HOCRF_DICTIONARY_DICTIONARY_CLASS_H_

#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "../libmarisa/marisa.h"

namespace Dictionary {

using std::pair;
using std::string;
using std::vector;

class DictionaryClass {
public:
    DictionaryClass(const string &filename, bool addPrefix);
    vector<pair<size_t, vector<string>>> commonPrefixSearch(const string &str) const;
    vector<string> lookup(const string &str) const;

private:
    vector<vector<size_t>> marisaIdToFeatureIdListList;
    vector<string> featureIdToStringList;
    marisa::Trie trie;
};

}  // namespace Dictionary

#endif  // HOCRF_DICTIONARY_DICTIONARY_CLASS_H_
