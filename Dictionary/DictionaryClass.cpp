#include "DictionaryClass.h"

#include "../libmarisa/marisa.h"

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Dictionary {

using std::cerr;
using std::endl;
using std::exit;
using std::getline;
using std::ifstream;
using std::make_pair;
using std::move;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::unordered_set;
using std::vector;

vector<string> splitStringByTabs(const string &s) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, '\t')) {
        elems.push_back(item);
    }
    return elems;
}

DictionaryClass::DictionaryClass(const string &filename) {
    ifstream ifs(filename);

    if (!ifs.is_open()) {
        cerr << "Cannot open the dictionary file: " << filename << endl;
        exit(1);
    }

    string line;
    size_t elementCount = 0;
    size_t lineNum = 0;
    
    unordered_map<string, size_t> stringToFeatureIdMap;
    unordered_map<string, vector<vector<size_t>>> wordToFeatureIdListListMap;
    
    marisa::Keyset keyset;
    
    while (getline(ifs, line)) {
        ++lineNum;
        vector<string> elems = splitStringByTabs(line);
        if (elementCount == 0) {
            if (elems.size() < 2) {
                cerr << "A dictionary entry must have one or more features." << endl;
                exit(1);
            }
            elementCount = elems.size() - 1;
        }
        if (elementCount != elems.size() - 1) {
            cerr << "Element numbers not consistent in " << filename << ", line number " << lineNum << "." << endl;
            exit(1);
        }
        const string &word = elems[0];
        if (word.empty()) {
            cerr << "Empty entry: line number " << lineNum << endl;
        }
        keyset.push_back(word.c_str());
        
        auto it = wordToFeatureIdListListMap.find(word);
        if (it == wordToFeatureIdListListMap.end()) {
            it = wordToFeatureIdListListMap.insert(make_pair(word, vector<vector<size_t>>())).first;
        }
        
        auto &featureIdListList = it->second;
        vector<size_t> t;
        t.reserve(elementCount);
        for (size_t i = 0; i < elementCount; ++i) {
            const string &elem = elems[i + 1];
            const auto it = stringToFeatureIdMap.find(elem);
            size_t featureId;
            if (it == stringToFeatureIdMap.end()) {
                featureId = stringToFeatureIdMap.size();
                stringToFeatureIdMap.insert(make_pair(elem, featureId));
            } else {
                featureId = it->second;
            }
            t.push_back(featureId);
        }
        featureIdListList.push_back(move(t));
    }
    // builds trie
    trie.build(keyset);

    // builds marisaIdToFeatureIdListListList
    size_t numKeys = trie.num_keys();
    marisaIdToFeatureIdListListList.clear();
    marisaIdToFeatureIdListListList.reserve(numKeys);
    marisa::Agent agent;
    for (size_t i = 0; i < numKeys; ++i) {
        agent.set_query(i);
        trie.reverse_lookup(agent);
        string key(agent.key().ptr(), agent.key().length());
        auto &featureIdListList = wordToFeatureIdListListMap.at(key);
        marisaIdToFeatureIdListListList.push_back(move(featureIdListList));
    }

    // builds featureIdToStringList
    featureIdToStringList.resize(stringToFeatureIdMap.size());
    for (const auto &entry : stringToFeatureIdMap) {
        featureIdToStringList[entry.second] = move(entry.first);
    }
}

vector<vector<const string *>> convertIdListListToStringListList(const vector<vector<size_t>> &idListList, const vector<string> &idToStringList) {
    vector<vector<const string *>> ret;
    ret.reserve(idListList.size());
    for (const auto &idList : idListList) {
        vector<const string *> t;
        t.reserve(idList.size());
        for (const auto &id : idList) {
            t.push_back(&idToStringList[id]);
        }
        ret.push_back(move(t));
    }
    return ret;
}

vector<pair<size_t, vector<vector<const string *>>>> DictionaryClass::commonPrefixSearch(const string &str) const {
    vector<pair<size_t, vector<vector<const string *>>>> ret;
    marisa::Agent agent;
    agent.set_query(str.c_str(), str.length());
    while (trie.common_prefix_search(agent)) {
        size_t marisaId = agent.key().id();
        size_t keyLen = agent.key().length();
        const auto &featureIdListList = marisaIdToFeatureIdListListList[marisaId];
        auto featureListList = convertIdListListToStringListList(featureIdListList, featureIdToStringList);
        ret.push_back(make_pair(keyLen, move(featureListList)));
    }
    return ret;
}

vector<vector<const string *>> DictionaryClass::lookup(const string &str) const {
    marisa::Agent agent;
    agent.set_query(str.c_str(), str.length());
    if (trie.lookup(agent)) {
        size_t marisaId = agent.key().id();
        size_t keyLen = agent.key().length();
        const auto &featureIdListList = marisaIdToFeatureIdListListList[marisaId];
        return convertIdListListToStringListList(featureIdListList, featureIdToStringList);
    }
    return vector<vector<const string *>>();
}

}  // namespace Dictionary
