#include "HighOrderCRFData.h"

#include "FeatureTemplate.h"
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
using std::move;
using std::ofstream;
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

HighOrderCRFData::HighOrderCRFData(unordered_map<shared_ptr<FeatureTemplate>, vector<uint32_t>> featureTemplateToFeatureIndexListMap, vector<double> weightList, vector<uint32_t> featureLabelSequenceIndexList, vector<LabelSequence> labelSequenceList, unordered_map<string, label_t> labelMap) {
    this->featureTemplateToFeatureIndexListMap = move(featureTemplateToFeatureIndexListMap);
    this->featureLabelSequenceIndexList = move(featureLabelSequenceIndexList);
    this->labelSequenceList = move(labelSequenceList);
    this->labelMap = move(labelMap);
    this->weightList.reserve(weightList.size());
    for (auto w : weightList) {
        this->weightList.push_back(double_to_weight(w));
    }
}

HighOrderCRFData::HighOrderCRFData() {}

const unordered_map<shared_ptr<FeatureTemplate>, vector<uint32_t>> &HighOrderCRFData::getFeatureTemplateToFeatureIndexMapList() const {
    return featureTemplateToFeatureIndexListMap;
}

const vector<weight_t> &HighOrderCRFData::getWeightList() const {
    return weightList;
}

const vector<uint32_t> &HighOrderCRFData::getFeatureLabelSequenceIndexList() const {
    return featureLabelSequenceIndexList;
}

const vector<LabelSequence> &HighOrderCRFData::getLabelSequenceList() const {
    return labelSequenceList;
}

const unordered_map<string, label_t> &HighOrderCRFData::getLabelMap() const {
    return labelMap;
}

vector<string> HighOrderCRFData::getLabelStringList() const {
    vector<string> ret(labelMap.size());
    for (auto &entry : labelMap) {
        ret[entry.second] = entry.first;
    }
    return ret;
}

void HighOrderCRFData::read(const string &filename) {
    ifstream in(filename, ios::in | ios::binary);
    vector<char> buffer;

    buffer.reserve(1024);  // a buffer of an arbitrary size
    uint32_t bufferSize = 0;

    // reads feature templates
    uint32_t numFeatureTemplates = readNumber<uint32_t>(&in);
    featureTemplateToFeatureIndexListMap.clear();
    featureTemplateToFeatureIndexListMap.reserve(numFeatureTemplates);
    for (size_t i = 0; i < numFeatureTemplates; ++i) {
        // reads the observation of a feature template
        string obs = readString(&in, &buffer);

        // reads the label length
        uint32_t labelLength =  readNumber<uint32_t>(&in);
        auto ft = make_shared<FeatureTemplate>(obs, labelLength);

        // reads the feature indexes
        uint32_t featureIndexCount = readNumber<uint32_t>(&in);
        vector<uint32_t> featureIndexes;
        featureIndexes.reserve(featureIndexCount);
        for (size_t j = 0; j < featureIndexCount; ++j) {
            featureIndexes.push_back(readNumber<uint32_t>(&in));
        }
        featureTemplateToFeatureIndexListMap.insert(make_pair(ft, featureIndexes));
    }

    // read features
    uint32_t numFeatures = readNumber<uint32_t>(&in);
    weightList.clear();
    weightList.reserve(numFeatures);
    featureLabelSequenceIndexList.clear();
    featureLabelSequenceIndexList.reserve(numFeatures);
    for (size_t i = 0; i < numFeatures; ++i) {
        weight_t t = readNumber<weight_t>(&in);
        weightList.push_back(t);
        featureLabelSequenceIndexList.push_back(readNumber<uint32_t>(&in));
    }

    // read label sequences
    uint32_t numLabelSequences = readNumber<uint32_t>(&in);
    labelSequenceList.clear();
    labelSequenceList.reserve(numLabelSequences);
    for (size_t i = 0; i < numLabelSequences; ++i) {
        uint32_t len = readNumber<uint32_t>(&in);
        vector<label_t> v;
        for (size_t j = 0; j < len; ++j) {
            v.push_back(readNumber<uint32_t>(&in));
        }
        labelSequenceList.push_back(move(v));
    }

    // reads the label map
    uint32_t numLabels = readNumber<uint32_t>(&in);
    labelMap.clear();

    for (size_t i = 0; i < numLabels; ++i) {
        // reads the label string
        string labelString = readString(&in, &buffer);
        labelMap.insert(make_pair(labelString, i));
    }

    in.close();
}

void HighOrderCRFData::trim() {
    // trim features
    uint32_t validFeatureCount = 0;
    vector<uint32_t> validFeatureIndexList;
    validFeatureIndexList.reserve(weightList.size());
    vector<bool> flagList(labelSequenceList.size());
    for (size_t i = 0; i < weightList.size(); ++i) {
        if (weightList[i] != 0) {
            flagList[featureLabelSequenceIndexList[i]] = true;
            weightList[validFeatureCount] = weightList[i];
            featureLabelSequenceIndexList[validFeatureCount] = featureLabelSequenceIndexList[i];
            validFeatureIndexList.push_back(validFeatureCount);
            ++validFeatureCount;
        }
        else {
            validFeatureIndexList.push_back(UINT32_MAX);
        }
    }
    weightList.resize(validFeatureCount);
    featureLabelSequenceIndexList.resize(validFeatureCount);

    // trim label sequence list
    uint32_t validLabelSequenceCount = 0;
    vector<uint32_t> validLabelSequenceIndexList;
    validLabelSequenceIndexList.reserve(labelSequenceList.size());
    for (size_t i = 0; i < labelSequenceList.size(); ++i) {
        validLabelSequenceIndexList.push_back(flagList[i] ? validLabelSequenceCount : UINT32_MAX);
        if (flagList[i]) {
            if (validLabelSequenceCount != i) {
                labelSequenceList[validLabelSequenceCount] = move(labelSequenceList[i]);
            }
            ++validLabelSequenceCount;
        }
    }
    labelSequenceList.resize(validLabelSequenceCount);

    // update features
    for (auto &i : featureLabelSequenceIndexList) {
        i = validLabelSequenceIndexList[i];
    }

    // trim feature templates
    for (auto it = featureTemplateToFeatureIndexListMap.begin(); it != featureTemplateToFeatureIndexListMap.end(); ) {
        auto &v = it->second;
        vector<uint32_t> validFeatureIndexes;
        for (auto i : v) {
            auto newIndex = validFeatureIndexList[i];
            if (newIndex != UINT32_MAX) {
                validFeatureIndexes.push_back(newIndex);
            }
        }
        if (validFeatureIndexes.empty()) {
            featureTemplateToFeatureIndexListMap.erase(it++);
        }
        else {
            v = move(validFeatureIndexes);
            ++it;
        }
    }
}

void HighOrderCRFData::write(const string &filename) const {
    ofstream out(filename, ios::out | ios::binary);

    // write feature templates
    writeNumber<uint32_t>(&out, featureTemplateToFeatureIndexListMap.size());
    for (auto entry : featureTemplateToFeatureIndexListMap) {
        auto &ft = entry.first;
        auto &v = entry.second;
        writeString(&out, ft->getObservation());
        writeNumber<uint32_t>(&out, ft->getLabelLength());
        writeNumber<uint32_t>(&out, v.size());
        for (auto &i : v) {
            writeNumber<uint32_t>(&out, i);
        }
    }

    // write features
    writeNumber<uint32_t>(&out, weightList.size());
    for (size_t i = 0; i < weightList.size(); ++i) {
        writeNumber<weight_t>(&out, weightList[i]);  // assuming that the size of double is 64 bits
        writeNumber<uint32_t>(&out, featureLabelSequenceIndexList[i]);
    }

    // write label sequences
    writeNumber<uint32_t>(&out, labelSequenceList.size());
    for (auto &l : labelSequenceList) {
        writeNumber<uint32_t>(&out, l.getLength());
        for (size_t j = 0; j < l.getLength(); ++j) {
            writeNumber<label_t>(&out, l.getLabelAt(j));
        }
    }

    auto labelStringList = getLabelStringList();
    writeNumber<uint32_t>(&out, labelStringList.size());
    for (auto &str : labelStringList) {
        writeString(&out, str);
    }
    
    out.close();
}

void HighOrderCRFData::dumpFeatures(const string &filename, bool outputWeights) const {
    ofstream out(filename, ios::binary);
    out.precision(15);
    auto labelStringList = getLabelStringList();
    for (auto &entry : featureTemplateToFeatureIndexListMap) {
        auto &ft = entry.first;
        auto &v = entry.second;

        for (auto &featureIndex : v) {
            if (outputWeights) {
                out << weight_to_double(weightList[featureIndex]) << "\t";
            }
            out << (ft->getObservation().empty() ? "LABEL" : ft->getObservation());
            auto &labelSequence = labelSequenceList[featureIndex];
            for (size_t j = 0; j < labelSequence.getLength(); ++j) {
                out << "\t" << labelStringList[labelSequence.getLabelAt(j)];
            }
            out << endl;
        }
    }
    out.close();
}

}  // namespace HighOrderCRF
