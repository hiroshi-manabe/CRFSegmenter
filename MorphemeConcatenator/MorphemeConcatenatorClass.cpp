#include "MorphemeConcatenatorClass.h"

#include "../Dictionary/DictionaryClass.h"

#include <algorithm>
#include <cassert>
#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

namespace MorphemeConcatenator {

using Dictionary::DictionaryClass;
using std::make_pair;
using std::make_shared;
using std::move;
using std::map;
using std::pair;
using std::set;
using std::string;
using std::unordered_set;
using std::vector;

MorphemeConcatenatorClass::MorphemeConcatenatorClass(const unordered_set<string> &dictionaries) {
    assert(!dictionaries.empty());
    dictionary = make_shared<DictionaryClass>(dictionaries);
};

vector<vector<string>> MorphemeConcatenatorClass::concatenate(const vector<vector<string>> &sentence) const {
    set<size_t> posSet{0};
    string allSentence;
    map<size_t, vector<vector<string>>> nodeMap;
    
    size_t pos = 0;
    for (const auto &line : sentence) {
        const auto &word = line[0];
        allSentence += word;
        nodeMap.insert(make_pair(pos, vector<vector<string>>())).first->second.emplace_back(line);  // copied
        pos += word.size();
        posSet.insert(pos);
    }

    size_t prevPos = 0;
    for (size_t pos : posSet) {
        if (pos == 0) {
            continue;
        }
        auto results = dictionary->commonPrefixSearch(allSentence.substr(prevPos));
        for (const auto &result : results) {
            if (posSet.find(prevPos + result.first) != posSet.end() &&
                prevPos + result.first != pos) {
                const auto &firstResult = *result.second.begin();  // only uses the first one
                vector<string> temp;
                temp.reserve(firstResult.size() + 1);
                temp.emplace_back(allSentence.substr(prevPos, result.first));
                for (auto &p : firstResult) {
                    temp.emplace_back(move(p));  // copied
                }
                nodeMap.insert(make_pair(prevPos, vector<vector<string>>())).first->second.emplace_back(move(temp));
            }
        }
        prevPos = pos;
    }

    // get the shortest path
    map<size_t, pair<size_t, vector<string>>> shortestPathMap;
    for (auto &nodePair : nodeMap) {
        size_t pos = nodePair.first;
        size_t count = pos == 0 ? 0 : shortestPathMap[pos].first;
        for (auto &line : nodePair.second) {
            size_t endPos = pos + line[0].size();
            auto it = shortestPathMap.find(endPos);
            if (it == shortestPathMap.end()) {
                shortestPathMap.insert(make_pair(endPos,
                                                 make_pair(count + 1, line)));
            }
            else if (count + 1 < it->second.first) {
                it->second.first = count + 1;
                it->second.second = move(line);
            }
        }
    }

    size_t curPos = allSentence.size();
    size_t resultLen = shortestPathMap[curPos].first;
    vector<vector<string>> result(resultLen);
    while (curPos != 0) {
        size_t index = shortestPathMap[curPos].first - 1;
        result[index] = move(shortestPathMap[curPos].second);
        curPos -= result[index][0].size();
    }
    return result;
}

}  // namespace MorphemeConcatenator
