#include "MaxEntData.h"
#include "Observation.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>


namespace MaxEnt {

using std::endl;
using std::ios;
using std::ifstream;
using std::make_pair;
using std::make_shared;
using std::ofstream;
using std::string;
using std::unordered_map;
using std::vector;

template<class T>
void readNumber(ifstream *ifs, T *num) {
    memset(num, 0, sizeof(T));
    unsigned char val;
    size_t shift = 0;
    for (size_t i = 0; i < sizeof(T); ++i) {
        ifs->read((char *)&val, 1);
        *num |= ((T)val << shift);
        shift += 8;
    }
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

void readString(ifstream *ifs, string *str, vector<char> *buffer) {
    uint32_t len;
    readNumber<uint32_t>(ifs, &len);
    if (len > buffer->size()) {
        buffer->resize(len);
    }
    ifs->read(buffer->data(), len);
    str->assign(buffer->begin(), buffer->begin() + len);
}

void writeString(ofstream *ofs, const string &str) {
    writeNumber<uint32_t>(ofs, str.size());
    ofs->write(str.data(), str.size());
}

MaxEntData::MaxEntData() {
    labelToIndexMap = make_shared<unordered_map<string, uint32_t>>();
    attrToIndexMap = make_shared<unordered_map<string, uint32_t>>();
    indexPairToFeatureIndexMap = make_shared<unordered_map<pair<uint32_t, uint32_t>, uint32_t>>();
    bestWeightList = make_shared<vector<double>>();
}

MaxEntData::MaxEntData(shared_ptr<unordered_map<string, uint32_t>> labelToIndexMap,
                       shared_ptr<unordered_map<string, uint32_t>> attrToIndexMap,
                       shared_ptr<unordered_map<pair<uint32_t, uint32_t>, uint32_t>> indexPairToFeatureIndexMap,
                       shared_ptr<vector<double>> bestWeightList) : labelToIndexMap(labelToIndexMap), attrToIndexMap(attrToIndexMap), indexPairToFeatureIndexMap(indexPairToFeatureIndexMap), bestWeightList(bestWeightList) {};

const shared_ptr<vector<double>> MaxEntData::getBestWeightList() const {
    return bestWeightList;
}

shared_ptr<unordered_map<string, uint32_t>> MaxEntData::getLabelToIndexMap() {
    return labelToIndexMap;
}

shared_ptr<unordered_map<string, uint32_t>> MaxEntData::getAttrToIndexMap() {
    return attrToIndexMap;
}

shared_ptr<unordered_map<pair<uint32_t, uint32_t>, uint32_t>> MaxEntData::getIndexPairToFeatureIndexMap() {
    return indexPairToFeatureIndexMap;
}

void MaxEntData::read(const string &filename) {
    ifstream in(filename, ios::in | ios::binary);
    vector<char> buffer;

    buffer.reserve(1024);  // a buffer of an arbitrary size

    {
        uint32_t num;
        readNumber<uint32_t>(&in, &num);
        labelToIndexMap->clear();
        labelToIndexMap->reserve(num);
        for (uint32_t i = 0; i < num; ++i) {
            string str;
            readString(&in, &str, &buffer);
            labelToIndexMap->insert(make_pair(str, i));
        }
    }
    
    {
        uint32_t num;
        readNumber<uint32_t>(&in, &num);
        attrToIndexMap->clear();
        attrToIndexMap->reserve(num);
        for (uint32_t i = 0; i < num; ++i) {
            string str;
            readString(&in, &str, &buffer);
            attrToIndexMap->insert(make_pair(str, i));
        }
    }
    
    {
        uint32_t num;
        readNumber<uint32_t>(&in, &num);
        indexPairToFeatureIndexMap->clear();
        indexPairToFeatureIndexMap->reserve(num);
        for (uint32_t i = 0; i < num; ++i) {
            uint32_t first;
            uint32_t second;
            readNumber<uint32_t>(&in, &first);
            readNumber<uint32_t>(&in, &second);
            indexPairToFeatureIndexMap->insert(make_pair(make_pair(first, second), i));
        }
    }

    {
        uint32_t num;
        readNumber<uint32_t>(&in, &num);
        bestWeightList->clear();
        bestWeightList->reserve(num);
        for (uint32_t i = 0; i < num; ++i) {
            double weight;
            readNumber<uint64_t>(&in, (uint64_t*)&weight);  // assuming that the size of double is 64 bits
            bestWeightList->push_back(weight);
        }
    }

    in.close();
}

void MaxEntData::write(const string &filename) const {
    ofstream out(filename, ios::out | ios::binary);

    {
        vector<string> v(labelToIndexMap->size());

        for (const auto &e : *labelToIndexMap) {
            v[e.second] = e.first;
        }
    
        writeNumber<uint32_t>(&out, v.size());
        for (uint32_t i = 0; i < v.size(); ++i) {
            writeString(&out, v[i]);
        }
    }

    {
        vector<string> v(attrToIndexMap->size());

        for (const auto &e : *attrToIndexMap) {
            v[e.second] = e.first;
        }
    
        writeNumber<uint32_t>(&out, (uint32_t)v.size());
        for (uint32_t i = 0; i < v.size(); ++i) {
            writeString(&out, v[i]);
        }
    }

    {
        vector<pair<size_t, size_t>> v(indexPairToFeatureIndexMap->size());

        for (const auto &e : *indexPairToFeatureIndexMap) {
            v[e.second] = e.first;
        }
    
        writeNumber<uint32_t>(&out, (uint32_t)v.size());
        for (uint32_t i = 0; i < v.size(); ++i) {
            writeNumber<size_t>(&out, v[i].first);
            writeNumber<size_t>(&out, v[i].second);
        }
    }

    {
        writeNumber<uint32_t>(&out, (uint32_t)bestWeightList->size());
        for (uint32_t i = 0; i < bestWeightList->size(); ++i) {
            double expectation = (*bestWeightList)[i];
            writeNumber<uint64_t>(&out, *((uint64_t*)(&expectation)));  // assuming that the size of double is 64 bits
        }
    }
    
    out.close();
}

}  // namespace MaxEnt
