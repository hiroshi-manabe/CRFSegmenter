#include "DictionaryClass.h"

#include "../libmarisa/marisa.h"

#include <fstream>
#include <iostream>
#include <memory>
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
using std::make_shared;
using std::move;
using std::shared_ptr;
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

DictionaryClass::DictionaryClass(const string &filename, bool addPrefix) {
    ifstream ifs(filename);

    if (!ifs.is_open()) {
        cerr << "Cannot open the dictionary file: " << filename << endl;
        exit(1);
    }

    string line;
    size_t elementCount = 0;
    size_t lineNum = 0;
    
    unordered_map<string, size_t> stringToFeatureIdMap;
    unordered_map<string, unordered_set<size_t>> wordToFeatureIdSetMap;
    vector<string> prefixList;
    
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
            prefixList.reserve(elementCount);
            for (size_t i = 0; i < elementCount; ++i) {
                stringstream ss;
                ss << i << "-";
                prefixList.push_back(ss.str());
            }
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
        
        auto it = wordToFeatureIdSetMap.find(word);
        if (it == wordToFeatureIdSetMap.end()) {
            it = wordToFeatureIdSetMap.insert(make_pair(word, unordered_set<size_t>())).first;
        }
        
        auto &featureIdSet = it->second;
        for (size_t i = 0; i < elementCount; ++i) {
            string elem;
            if (addPrefix) {
                elem = prefixList[i] + elems[i + 1];
            } else {
                elem = elems[i + 1];
            }
             
            const auto it = stringToFeatureIdMap.find(elem);
            size_t featureId;
            if (it == stringToFeatureIdMap.end()) {
                featureId = stringToFeatureIdMap.size();
                stringToFeatureIdMap.insert(make_pair(elem, featureId));
            } else {
                featureId = it->second;
            }
            featureIdSet.insert(featureId);
        }
    }
    // builds trie
    trie.build(keyset);

    // builds marisaIdToFeatureIdListList
    size_t numKeys = trie.num_keys();
    marisaIdToFeatureIdListList.clear();
    marisaIdToFeatureIdListList.reserve(numKeys);
    marisa::Agent agent;
    for (size_t i = 0; i < numKeys; ++i) {
        agent.set_query(i);
        trie.reverse_lookup(agent);
        string key(agent.key().ptr(), agent.key().length());
        const auto &featureIdSet = wordToFeatureIdSetMap.at(key);
        marisaIdToFeatureIdListList.push_back(vector<size_t>(featureIdSet.begin(), featureIdSet.end()));
    }

    // builds featureIdToStringList
    featureIdToStringList.resize(stringToFeatureIdMap.size());
    for (const auto &entry : stringToFeatureIdMap) {
        featureIdToStringList[entry.second] = move(entry.first);
    }
}

vector<pair<size_t, vector<string>>> DictionaryClass::commonPrefixSearch(const string &str) {
    vector<pair<size_t, vector<string>>> ret;
    marisa::Agent agent;
    agent.set_query(str.c_str(), str.length());
    while (trie.common_prefix_search(agent)) {
        size_t marisaId = agent.key().id();
        size_t keyLen = agent.key().length();
        const auto &featureIdList = marisaIdToFeatureIdListList[marisaId];
        vector<string> featureList;
        for (const auto &featureId : featureIdList) {
            featureList.push_back(featureIdToStringList[featureId]);
        }
        ret.push_back(make_pair(keyLen, move(featureList)));
    }
    return ret;
}

vector<string> DictionaryClass::lookup(const string &str) {
    vector<string> ret;
    marisa::Agent agent;
    agent.set_query(str.c_str(), str.length());
    if (trie.lookup(agent)) {
        size_t marisaId = agent.key().id();
        size_t keyLen = agent.key().length();
        const auto &featureIdList = marisaIdToFeatureIdListList[marisaId];
        vector<string> FeatureList;
        for (const auto &featureId : featureIdList) {
            ret.push_back(featureIdToStringList[featureId]);
        }
    }
    return ret;
}

}  // namespace Dictionary
