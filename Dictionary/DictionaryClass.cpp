#include "DictionaryClass.h"
#include "SingleDictionary.h"

#include "../libmarisa/marisa.h"
#include "../Utility/EncryptionUtil.h"
#include "../Utility/StringUtil.h"

#include <iterator>
#include <memory>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <utility>
#include <vector>

namespace Dictionary {

using std::back_inserter;
using std::inserter;
using std::make_shared;
using std::move;
using std::pair;
using std::set;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

DictionaryClass::DictionaryClass(const unordered_set<string> &files) {
    for (const auto &filename : files) {
        dictionaryList.emplace_back(make_shared<SingleDictionary>(filename, Utility::decrypt));
    }
}

vector<pair<size_t, set<vector<string>>>> DictionaryClass::commonPrefixSearch(const string &str) const {
    unordered_map<size_t, set<vector<string>>> tempMap;
    for (const auto &dictionary : dictionaryList) {
        auto t = dictionary->commonPrefixSearch(str);
        for (auto &p : t) {
            for (auto &v : p.second) {
                tempMap[p.first].emplace(move(v));
            }
        }
    }
    vector<pair<size_t, set<vector<string>>>> ret;
    for (auto &p : tempMap) {
        ret.emplace_back(make_pair(p.first, move(p.second)));
    }
    return ret;
}

set<vector<string>> DictionaryClass::lookup(const string &str) const {
    set<vector<string>> ret;
    for (const auto &dictionary : dictionaryList) {
        auto t = dictionary->lookup(str);
        move(t.begin(), t.end(), inserter(ret, ret.begin()));
    }
    return ret;
}

}  // namespace Dictionary
