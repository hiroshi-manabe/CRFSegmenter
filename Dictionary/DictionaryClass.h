#ifndef HOCRF_DICTIONARY_DICTIONARY_CLASS_H_
#define HOCRF_DICTIONARY_DICTIONARY_CLASS_H_

#include <cstdlib>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../libmarisa/marisa.h"

namespace Dictionary {

using std::pair;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

class DictionaryClass {
public:
    DictionaryClass(const string &filename, bool addPrefix);
    vector<pair<size_t, vector<string>>> commonPrefixSearch(const string &str);
    vector<string> lookup(const string &str);

private:
    vector<vector<size_t>> marisaIdToFeatureIdListList;
    vector<string> featureIdToStringList;
    marisa::Trie trie;
};

}  // namespace Dictionary

#endif  // HOCRF_DICTIONARY_DICTIONARY_CLASS_H_
