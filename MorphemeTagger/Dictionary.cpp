#include "Dictionary.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace MorphemeTagger {

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

Dictionary::Dictionary(const string &filename) {
    ifstream ifs(filename);

    if (!ifs.is_open()) {
        cerr << "Cannot open the dictionary file: " << filename << endl;
        exit(1);
    }

    string line;
    size_t elementCount = 0;
    size_t lineNum = 0;
    
    vector<unordered_map<string, size_t>> stringToIdMapList;
    
    while (getline(ifs, line)) {
        ++lineNum;
        vector<string> elems = splitStringByTabs(line);
        if (elementCount == 0) {
            if (elems.size() < 2) {
                cerr << "A dictionary entry must have one or more features." << endl;
                exit(1);
            }
            elementCount = elems.size() - 1;
            stringToIdMapList.resize(elementCount);
        }
        if (elementCount != elems.size() - 1) {
            cerr << "Element numbers not consistent in " << filename << ", line number " << lineNum << "." << endl;
            exit(1);
        }
        const string &entry = elems[0];
        if (entry.empty()) {
            cerr << "Empty entry: line number " << lineNum << endl;
        }

        vector<size_t> idList;
        for (size_t i = 0; i < elementCount; ++i) {
            const string &elem = elems[i + 1];
            auto &stringToIdMap = stringToIdMapList[i];
             
            auto it = stringToIdMap.find(elem);
            if (it == stringToIdMap.end()) {
                it = stringToIdMap.insert(make_pair(elem, stringToIdMap.size())).first;
            }
            idList.push_back(it->second);
        }
        
        auto it = idDict.find(entry);
        if (it == idDict.end()) {
            it = idDict.insert(make_pair(entry, vector<vector<size_t>>())).first;
        }
        it->second.push_back(move(idList));
    }
    
    // builds idToStringListList
    idToStringListList.resize(elementCount);
    for (size_t i = 0; i < elementCount; ++i) {
        auto &stringToIdMap = stringToIdMapList[i];
        auto &idToStringList = idToStringListList[i];
        idToStringList.resize(stringToIdMap.size());
        for (const auto &entry : stringToIdMap) {
            idToStringList[entry.second] = move(entry.first);
        }
    }
}

shared_ptr<vector<vector<string>>> Dictionary::lookup(const string &str) const {
    auto it = idDict.find(str);
    auto ret = make_shared<vector<vector<string>>>();
    if (it != idDict.end()) {
        for (const auto &idList : it->second) {
            ret->push_back(move(getStringList(idList)));
        }
    }
    return ret;
}

vector<string> Dictionary::getStringList(const vector<size_t> &idList) const {
    vector<string> ret;
    for (size_t i = 0; i < idToStringListList.size(); ++i) {
        auto &idToStringList = idToStringListList[i];
        ret.push_back(idToStringList[idList[i]]);
    }
    return ret;
}

}  // namespace MorphemeTagger
