#include "SingleDictionary.h"

#include "../libmarisa/marisa.h"
#include "../Utility/FileUtil.h"
#include "../Utility/StringUtil.h"

#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Dictionary {

using std::cerr;
using std::endl;
using std::exit;
using std::function;
using std::getline;
using std::ifstream;
using std::istream;
using std::istringstream;
using std::make_pair;
using std::move;
using std::ostream;
using std::ostringstream;
using std::pair;
using std::string;
using std::unordered_map;
using std::vector;

SingleDictionary::SingleDictionary(const string &file, function<void(char *, size_t)> decode) {
    ifstream ifs(file, std::ios::binary);
    size_t filesize = (size_t)Utility::getSize(ifs);

    string s(filesize, 0);
    char *p = &s[0];

    ifs.read(p, filesize);
    ifs.close();

    if (decode) {
        decode(p, filesize);
    }
    
    istringstream iss(s, std::ios::binary);
    
    uint32_t dummy;
    iss.read((char *)&dummy, sizeof(dummy));
    iss.read((char *)&numberOfFieldsPerLine, sizeof(numberOfFieldsPerLine));
    iss >> entryTrie;
    iss >> fieldTrie;
    
    lastLineIndexList.resize(entryTrie.num_keys());
    iss.read((char *)lastLineIndexList.data(), sizeof(lastLineIndexList[0]) * lastLineIndexList.size());
    uint32_t fieldIdCount;
    iss.read((char *)&fieldIdCount, sizeof(fieldIdCount));
    fieldIdList.resize(fieldIdCount);
    iss.read((char *)fieldIdList.data(), sizeof(fieldIdList[0]) * fieldIdList.size());
}

void SingleDictionary::build(istream &is, ostream &os, function<void(char *, size_t)> encode) {
    marisa::Trie entryTrie;
    marisa::Trie fieldTrie;
    
    string line;
    uint32_t fieldCount = 0;
    size_t lineNum = 0;
    
    unordered_map<string, vector<vector<string>>> entryToLineListMap;
    
    marisa::Keyset entryKeyset;
    marisa::Keyset fieldKeyset;
    
    while (getline(is, line)) {
        ++lineNum;
        vector<string> entryAndFields = Utility::splitString(line);
        if (fieldCount == 0) {
            if (entryAndFields.size() < 2) {
                cerr << "A dictionary entry must have one or more entryAndFields." << endl;
                exit(1);
            }
            fieldCount = entryAndFields.size() - 1;
        }
        if (fieldCount != entryAndFields.size() - 1) {
            cerr << "Field numbers not consistent: line number " << lineNum << "." << endl;
            exit(1);
        }
        const string &entry = entryAndFields[0];
        vector<string> fields(entryAndFields.begin() + 1, entryAndFields.end());
        if (entry.empty()) {
            cerr << "Empty entry: line number " << lineNum << "." << endl;
            exit(1);
        }
        entryKeyset.push_back(entry.c_str());
        for (const auto &field : fields) {
            fieldKeyset.push_back(field.c_str());
        }
        entryToLineListMap[entry].emplace_back(move(fields));
    }
    // builds tries
    entryTrie.build(entryKeyset);
    fieldTrie.build(fieldKeyset);

    vector<uint32_t> lastLineIndexList;
    vector<uint32_t> fieldIdList;
    uint32_t lastLineIndex = 0;

    size_t entryCount = entryTrie.num_keys();
    marisa::Agent entryAgent;
    marisa::Agent fieldAgent;
    for (size_t i = 0; i < entryCount; ++i) {
        entryAgent.set_query(i);
        entryTrie.reverse_lookup(entryAgent);
        string key(entryAgent.key().ptr(), entryAgent.key().length());
        const auto &lineList = entryToLineListMap.at(key);
        lastLineIndex += lineList.size();
        lastLineIndexList.emplace_back(lastLineIndex);
        for (const auto &line : lineList) {
            for (const auto &field : line) {
                fieldAgent.set_query(field.c_str(), field.length());
                fieldTrie.lookup(fieldAgent);
                fieldIdList.emplace_back(fieldAgent.key().id());
            }
        }
    }

    ostringstream oss(std::ios::binary);
    uint32_t dummy = 0;
    oss.write((char *)&dummy, sizeof(dummy));
    oss.write((char *)&fieldCount, sizeof(fieldCount));
    oss << entryTrie;
    oss << fieldTrie;
    
    oss.write((char *)lastLineIndexList.data(), sizeof(lastLineIndexList[0]) * lastLineIndexList.size());
    uint32_t fieldIdCount = fieldIdList.size();
    oss.write((char *)&fieldIdCount, sizeof(fieldIdCount));
    oss.write((char *)fieldIdList.data(), sizeof(fieldIdList[0]) * fieldIdList.size());

    size_t pos = (size_t)oss.tellp();
    string s = oss.str();
    char *p = &s[0];

    if (encode) {
        encode(p, pos);
    }
    
    os.write(&s[0], pos);
}

vector<vector<string>> SingleDictionary::getLines(size_t entryId) const {
    vector<vector<string>> ret;
    size_t line = entryId > 0 ? lastLineIndexList[entryId - 1] : 0;
    size_t lineEnd = lastLineIndexList[entryId];
    ret.reserve(lineEnd - line);
    marisa::Agent fieldAgent;
    
    for (; line < lineEnd; ++line) {
        vector<string> t;
        t.reserve(numberOfFieldsPerLine);
        for (size_t i = 0; i < numberOfFieldsPerLine; ++i) {
            fieldAgent.set_query(fieldIdList[line * numberOfFieldsPerLine + i]);
            fieldTrie.reverse_lookup(fieldAgent);
            t.emplace_back(fieldAgent.key().ptr(), fieldAgent.key().length());
        }
        ret.emplace_back(move(t));
    }
    return ret;
}

vector<pair<size_t, vector<vector<string>>>> SingleDictionary::commonPrefixSearch(const string &str) const {
    vector<pair<size_t, vector<vector<string>>>> ret;
    marisa::Agent entryAgent;
    entryAgent.set_query(str.c_str(), str.length());
    while (entryTrie.common_prefix_search(entryAgent)) {
        size_t entryId = entryAgent.key().id();
        size_t entryLen = entryAgent.key().length();
        auto lines = getLines(entryId);
        ret.emplace_back(make_pair(entryLen, move(lines)));
    }
    return ret;
}

vector<vector<string>> SingleDictionary::lookup(const string &str) const {
    marisa::Agent entryAgent;
    entryAgent.set_query(str.c_str(), str.length());
    if (entryTrie.lookup(entryAgent)) {
        size_t entryId = entryAgent.key().id();
        return getLines(entryId);
    }
    return vector<vector<string>>();
}

}  // namespace Dictionary
