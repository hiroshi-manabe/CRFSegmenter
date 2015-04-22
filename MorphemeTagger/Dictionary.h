#ifndef HOCRF_MORPHEME_TAGGER_DICTIONARY_H_
#define HOCRF_MORPHEME_TAGGER_DICTIONARY_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace MorphemeTagger {

using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

class Dictionary {
public:
    Dictionary(const string &filename);
    shared_ptr<vector<vector<string>>> lookup(const string &str) const;

private:
    vector<string> getStringList(const vector<size_t> &idList) const;
    unordered_map<string, vector<vector<size_t>>> idDict;
    vector<vector<string>> idToStringListList;
};

}  // namespace MorphemeTagger

#endif  // HOCRF_MORPHEME_TAGGER_DICTIONARY_H_
