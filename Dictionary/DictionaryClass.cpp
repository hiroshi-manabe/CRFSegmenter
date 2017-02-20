#include "DictionaryClass.h"
#include "SingleDictionary.h"

#include "../libmarisa/marisa.h"
#include "../Utility/StringUtil.h"

#include <iterator>
#include <memory>
#include <unordered_set>
#include <string>
#include <utility>
#include <vector>

namespace Dictionary {

using std::back_inserter;
using std::make_shared;
using std::move;
using std::pair;
using std::string;
using std::unordered_set;
using std::vector;

DictionaryClass::DictionaryClass(const unordered_set<string> &files, void(*decode)(char *, size_t)) {
    for (const auto &filename : files) {
        dictionaryList.emplace_back(make_shared<SingleDictionary>(filename, decode));
    }
}

vector<pair<size_t, vector<vector<string>>>> DictionaryClass::commonPrefixSearch(const string &str) const {
    vector<pair<size_t, vector<vector<string>>>> ret;
    for (const auto &dictionary : dictionaryList) {
        auto t = dictionary->commonPrefixSearch(str);
        move(t.begin(), t.end(), std::back_inserter(ret));
    }
    return ret;
}

vector<vector<string>> DictionaryClass::lookup(const string &str) const {
    vector<vector<string>> ret;
    for (const auto &dictionary : dictionaryList) {
        auto t = dictionary->lookup(str);
        move(t.begin(), t.end(), back_inserter(ret));
    }
    return ret;
}

}  // namespace Dictionary
