#include "MaxEntData.h"
#include "Observation.h"

#include <cassert>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>


namespace MaxEnt {

using std::ios;
using std::ifstream;
using std::make_pair;
using std::ofstream;
using std::pair;
using std::string;
using std::unordered_map;
using std::vector;

template<class T>
T readNumber(ifstream *ifs) {
    T num;
    memset(&num, 0, sizeof(T));
    unsigned char val;
    size_t shift = 0;
    for (size_t i = 0; i < sizeof(T); ++i) {
        ifs->read((char *)&val, 1);
        num |= ((T)val << shift);
        shift += 8;
    }
    return num;
}

template<class T>
void writeNumber(ofstream *ofs, T num) {
    unsigned char val;
    size_t shift = 0;
    for (size_t i = 0; i < sizeof(T); ++i) {
        val = num >> shift & 0xff;
        ofs->write((char *)&val, 1);
        shift += 8;
    }
}

string readString(ifstream *ifs, vector<char> *buffer) {
    string str;
    uint32_t len = readNumber<uint32_t>(ifs);
    if (len > buffer->size()) {
        buffer->resize(len);
    }
    ifs->read(buffer->data(), len);
    str.assign(buffer->begin(), buffer->begin() + len);
    return str;
}

void writeString(ofstream *ofs, const string &str) {
    writeNumber<uint32_t>(ofs, str.size());
    ofs->write(str.data(), str.size());
}

MaxEntData::MaxEntData() {}

MaxEntData::MaxEntData(unordered_map<string, uint32_t> labelToIndexMap,
    unordered_map<string, uint32_t> attrToIndexMap,
    unordered_map<pair<uint32_t, uint32_t>, uint32_t> indexPairToFeatureIndexMap,
    vector<double> bestWeightList) {
    this->labelToIndexMap = move(labelToIndexMap);
    this->attrToIndexMap = move(attrToIndexMap);
    this->indexPairToFeatureIndexMap = move(indexPairToFeatureIndexMap);
    this->bestWeightList = move(bestWeightList);
}

const vector<double> &MaxEntData::getBestWeightList() const {
    return bestWeightList;
}

unordered_map<string, uint32_t> &MaxEntData::getLabelToIndexMap() {
    return labelToIndexMap;
}

unordered_map<string, uint32_t> &MaxEntData::getAttrToIndexMap() {
    return attrToIndexMap;
}

unordered_map<pair<uint32_t, uint32_t>, uint32_t> &MaxEntData::getIndexPairToFeatureIndexMap() {
    return indexPairToFeatureIndexMap;
}

void MaxEntData::read(const string &filename) {
    ifstream in(filename, ios::in | ios::binary);
    vector<char> buffer;

    buffer.reserve(1024);  // a buffer of an arbitrary size

    {
        uint32_t num = readNumber<uint32_t>(&in);
        labelToIndexMap.clear();
        labelToIndexMap.reserve(num);
        for (uint32_t i = 0; i < num; ++i) {
            string str =  readString(&in, &buffer);
            labelToIndexMap.insert(make_pair(str, i));
        }
    }
    
    {
        uint32_t num = readNumber<uint32_t>(&in);
        attrToIndexMap.clear();
        attrToIndexMap.reserve(num);
        for (uint32_t i = 0; i < num; ++i) {
            string str = readString(&in, &buffer);
            attrToIndexMap.insert(make_pair(str, i));
        }
    }
    
    uint32_t featureNum = readNumber<uint32_t>(&in);
    {
        indexPairToFeatureIndexMap.clear();
        indexPairToFeatureIndexMap.reserve(featureNum);
        for (uint32_t i = 0; i < featureNum; ++i) {
            uint32_t first = readNumber<uint32_t>(&in);
            uint32_t second = readNumber<uint32_t>(&in);
            indexPairToFeatureIndexMap.insert(make_pair(make_pair(first, second), i));
        }
    }

    {
        bestWeightList.clear();
        bestWeightList.reserve(featureNum);
        for (uint32_t i = 0; i < featureNum; ++i) {
            uint64_t t = readNumber<uint64_t>(&in);  // assuming that the size of double is 64 bits
            bestWeightList.push_back(*(double *)&t);
        }
    }

    in.close();
}

void MaxEntData::trim() {
    // set valid attribute flags
    vector<bool> attributeIsValidFlagList(attrToIndexMap.size());
    for (auto &entry : indexPairToFeatureIndexMap) {
        auto &attrIndex = entry.first.second;
        auto &featureIndex = entry.second;
        if (bestWeightList[featureIndex] != 0.0) {
            attributeIsValidFlagList[attrIndex] = true;
        }
    }

    // generate the mapping table of old and new indexes
    vector<uint32_t> validAttributeIndexList;
    validAttributeIndexList.reserve(attrToIndexMap.size());
    size_t validAttributeCount = 0;
    for (size_t i = 0; i < attrToIndexMap.size(); ++i) {
        if (attributeIsValidFlagList[i]) {
            validAttributeIndexList.push_back(validAttributeCount);
            ++validAttributeCount;
        }
        else {
            validAttributeIndexList.push_back(UINT32_MAX);
        }
    }

    // trim the attribute-to-index map
    for (auto it = attrToIndexMap.begin(); it != attrToIndexMap.end(); ) {
        auto &attrIndex = it->second;
        auto newAttrIndex = validAttributeIndexList[attrIndex];
        if (newAttrIndex == UINT32_MAX) {
            attrToIndexMap.erase(it++);
        }
        else {
            attrIndex = newAttrIndex;
            ++it;
        }
    }

    // trim the best weight list
    uint32_t validFeatureCount = 0;
    vector<uint32_t> validFeatureIndexList;
    validFeatureIndexList.reserve(bestWeightList.size());
    for (size_t i = 0; i < bestWeightList.size(); ++i) {
        if (bestWeightList[i] != 0.0) {
            validFeatureIndexList.push_back(validFeatureCount);
            bestWeightList[validFeatureCount] = bestWeightList[i];
            ++validFeatureCount;
        }
        else {
            validFeatureIndexList.push_back(UINT32_MAX);
        }
    }
    bestWeightList.resize(validFeatureCount);

    // generate a new label-attribute-pair-to-feature-index map
    unordered_map<pair<uint32_t, uint32_t>, uint32_t> newMap;
    for (auto entry : indexPairToFeatureIndexMap) {
        auto &pair = entry.first;
        auto &featureIndex = entry.second;
        auto &labelIndex = pair.first;
        auto &attrIndex = pair.second;
        auto newAttrIndex = validAttributeIndexList[attrIndex];
        auto newFeatureIndex = validFeatureIndexList[featureIndex];
        if (newAttrIndex != UINT32_MAX && newFeatureIndex != UINT32_MAX) {
            newMap.insert(make_pair(make_pair(labelIndex, newAttrIndex), newFeatureIndex));
        }
    }
    indexPairToFeatureIndexMap = move(newMap);
}

void MaxEntData::write(const string &filename) const {
    ofstream out(filename, ios::out | ios::binary);

    {
        vector<string> v(labelToIndexMap.size());

        for (const auto &e : labelToIndexMap) {
            v[e.second] = e.first;
        }
    
        writeNumber<uint32_t>(&out, v.size());
        for (uint32_t i = 0; i < v.size(); ++i) {
            writeString(&out, v[i]);
        }
    }

    {
        vector<string> v(attrToIndexMap.size());

        for (const auto &e : attrToIndexMap) {
            v[e.second] = e.first;
        }
    
        writeNumber<uint32_t>(&out, (uint32_t)v.size());
        for (uint32_t i = 0; i < v.size(); ++i) {
            writeString(&out, v[i]);
        }
    }

    {
        vector<pair<uint32_t, uint32_t>> v(indexPairToFeatureIndexMap.size());

        for (const auto &e : indexPairToFeatureIndexMap) {
            v[e.second] = e.first;
        }
    
        assert(bestWeightList.size() == bestWeightList.size());
        writeNumber<uint32_t>(&out, (uint32_t)v.size());
        for (uint32_t i = 0; i < v.size(); ++i) {
            writeNumber<uint32_t>(&out, v[i].first);
            writeNumber<uint32_t>(&out, v[i].second);
        }
    }

    {
        for (uint32_t i = 0; i < bestWeightList.size(); ++i) {
            double expectation = bestWeightList[i];
            writeNumber<uint64_t>(&out, *((uint64_t*)(&expectation)));  // assuming that the size of double is 64 bits
        }
    }
    
    out.close();
}

}  // namespace MaxEnt
