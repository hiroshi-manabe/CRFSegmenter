#include "HighOrderCRFData.h"

#include "Feature.h"
#include "LabelSequence.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>


namespace HighOrderCRF {

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

HighOrderCRFData::HighOrderCRFData(shared_ptr<vector<shared_ptr<Feature>>> featureList, shared_ptr<vector<double>> bestWeightList, shared_ptr<unordered_map<string, label_t>> labelMap) : featureList(featureList), bestWeightList(bestWeightList), labelMap(labelMap) {}
HighOrderCRFData::HighOrderCRFData() {}

shared_ptr<vector<shared_ptr<Feature>>> HighOrderCRFData::getFeatureList() const {
    return featureList;
}

shared_ptr<vector<double>> HighOrderCRFData::getBestWeightList() const {
    return bestWeightList;
}

shared_ptr<unordered_map<string, label_t>> HighOrderCRFData::getLabelMap() const {
    return labelMap;
}

shared_ptr<vector<string>> HighOrderCRFData::getLabelStringList() const {
    auto ret = make_shared<vector<string>>(labelMap->size());
    for (auto &entry : *labelMap) {
        (*ret)[entry.second] = entry.first;
    }
    return ret;
}

void HighOrderCRFData::read(const string &filename) {
    ifstream in(filename, ios::in | ios::binary);
    vector<char> buffer;

    buffer.reserve(1024);  // a buffer of an arbitrary size
    uint32_t bufferSize = 0;

    // reads features
    uint32_t numFeatures;
    readNumber<uint32_t>(&in, &numFeatures);
    auto featureList = make_shared<vector<shared_ptr<Feature>>>();
    featureList->reserve(numFeatures);
    auto bestWeightList = make_shared<vector<double>>(numFeatures);

    for (uint32_t i = 0; i < numFeatures; ++i) {
        // reads the observation of a feature
        string obs;
        readString(&in, &obs, &buffer);

        // reads the labels
        uint32_t labelLength;
        readNumber<uint32_t>(&in, &labelLength);
        auto labels = make_shared<vector<label_t>>(labelLength);
        for (size_t j = 0; j < labelLength; ++j) {
            label_t label;
            readNumber<label_t>(&in, &label);
            (*labels)[j] = label;
        }
        double weight;
        readNumber<uint64_t>(&in, (uint64_t*)&weight);  // assuming that the size of double is 64 bits
        featureList->push_back(make_shared<Feature>(obs, make_shared<LabelSequence>(labels), i));
        (*bestWeightList)[i] = weight;
    }

    // reads the label map
    uint32_t numLabels;
    in.read((char *)&numLabels, sizeof(uint32_t));
    auto labelMap = make_shared<unordered_map<string, label_t>>();

    for (uint32_t i = 0; i < numLabels; ++i) {
        // reads the label string
        string labelString;
        readString(&in, &labelString, &buffer);

        // reads the label number
        label_t labelNum;
        readNumber<label_t>(&in, &labelNum);

        labelMap->insert(make_pair(labelString, labelNum));
    }
    this->featureList = featureList;
    this->bestWeightList = bestWeightList;
    this->labelMap = labelMap;

    in.close();
}

void HighOrderCRFData::write(const string &filename) const {
    ofstream out(filename, ios::out | ios::binary);

    size_t validFeatureCount = 0;

    for (uint32_t i = 0; i < featureList->size(); ++i) {
        if ((*bestWeightList)[i] != 0.0) {
            ++validFeatureCount;
        }
    }

    writeNumber<uint32_t>(&out, validFeatureCount);

    for (uint32_t i = 0; i < featureList->size(); ++i) {
        auto &feature = (*featureList)[i];

        double expectation = (*bestWeightList)[i];
        if (expectation == 0.0) {
            continue;
        }
        // writes the observation of a feature
        writeString(&out, feature->getObservation());
        auto labelSequence = feature->getLabelSequence();
        writeNumber<uint32_t>(&out, labelSequence->getLength());
        for (size_t j = 0; j < labelSequence->getLength(); ++j) {
            writeNumber<label_t>(&out, labelSequence->getLabelAt(j));
        }
        writeNumber<uint64_t>(&out, *((uint64_t*)(&expectation)));  // assuming that the size of double is 64 bits
    }
    
    writeNumber<uint32_t>(&out, labelMap->size());
    for (auto &entry : *labelMap) {
        writeString(&out, entry.first);
        writeNumber<label_t>(&out, entry.second);
    }
    
    out.close();
}

void HighOrderCRFData::dumpFeatures(const string &filename, bool outputWeights) const {
    ofstream out(filename, ios::binary);
    out.precision(15);
    auto reversedLabelMap = getLabelStringList();
    for (size_t i = 0; i < featureList->size(); ++i) {
        auto &feature = (*featureList)[i];
        if (outputWeights) {
            out << (*bestWeightList)[i] << "\t";
        }
        out << (feature->getObservation().empty() ? "LABEL" : feature->getObservation());
        auto labelSequence = feature->getLabelSequence();
        for (size_t j = 0; j < labelSequence->getLength(); ++j) {
            out << "\t" << reversedLabelMap->at(labelSequence->getLabelAt(j));
        }
        out << endl;
    }
    out.close();
}

}  // namespace HighOrderCRF
