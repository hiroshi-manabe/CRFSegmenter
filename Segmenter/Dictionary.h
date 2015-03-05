#ifndef SEGMENTER_DICTIONARY_H_
#define SEGMENTER_DICTIONARY_H_

#include <cstdlib>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../libmarisa/marisa.h"

namespace Segmenter {

using std::pair;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

class Dictionary {
public:
    Dictionary(const string &filename);
    vector<pair<size_t, vector<string>>> lookup(const string &str);

private:
    vector<vector<size_t>> marisaIdToFeatureIdListList;
    vector<string> featureIdToStringList;
    marisa::Trie trie;
};

}  // namespace Segmenter

#endif  // SEGMENTER_DICTIONARY_H_
