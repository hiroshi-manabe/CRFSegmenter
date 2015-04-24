#include "MaxEntData.h"

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
    strToIndexMap = make_shared <unordered_map<string, size_t>>();
    bestWeightList = make_shared<vector<double>>();
}

MaxEntData::MaxEntData(shared_ptr<unordered_map<string, size_t>> strToIndexMap, shared_ptr<vector<double>> bestWeightList) : strToIndexMap(strToIndexMap), bestWeightList(bestWeightList) {}
    
const shared_ptr<vector<double>> MaxEntData::getBestWeightList() const {
    return bestWeightList;
}

shared_ptr<unordered_map<string, size_t>> MaxEntData::getStrToIndexMap() {
    return strToIndexMap;
}

void MaxEntData::read(const string &filename) {
    ifstream in(filename, ios::in | ios::binary);
    vector<char> buffer;

    buffer.reserve(1024);  // a buffer of an arbitrary size
    uint32_t bufferSize = 0;
    
    // reads features
    uint32_t numFeatures;
    readNumber<uint32_t>(&in, &numFeatures);
    strToIndexMap->clear();
    strToIndexMap->reserve(numFeatures);
    bestWeightList->clear();
    bestWeightList->resize(numFeatures);

    for (size_t i = 0; i < numFeatures; ++i) {
        string str;
        readString(&in, &str, &buffer);
        strToIndexMap->insert(make_pair(str, i));
        
        double weight;
        readNumber<uint64_t>(&in, (uint64_t*)&weight);  // assuming that the size of double is 64 bits
        (*bestWeightList)[i] = weight;
    }

    in.close();
}

void MaxEntData::write(const string &filename) const {
    ofstream out(filename, ios::out | ios::binary);

    vector<string> v(strToIndexMap->size());

    for (const auto &e : *strToIndexMap) {
        v[e.second] = e.first;
    }
    
    writeNumber<uint32_t>(&out, v.size());

    for (uint32_t i = 0; i < v.size(); ++i) {
        // writes the observation of a feature
        writeString(&out, v[i]);
        double expectation = (*bestWeightList)[i];
        writeNumber<uint64_t>(&out, *((uint64_t*)(&expectation)));  // assuming that the size of double is 64 bits
    }
    
    out.close();
}

void MaxEntData::dumpFeatures(const string &filename, bool outputWeights) const {
    ofstream out(filename, ios::binary);
    out.precision(15);
    vector<string> v(strToIndexMap->size());

    for (const auto &e : *strToIndexMap) {
        v[e.second] = e.first;
    }
    
    for (size_t i = 0; i < v.size(); ++i) {
        if (outputWeights) {
            out << (*bestWeightList)[i] << "\t";
        }
        out << v[i] << endl;
    }
    out.close();
}

}  // namespace MaxEnt
