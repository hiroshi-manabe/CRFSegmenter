#include "DataSequence.h"

#include "FeatureTemplate.h"
#include "Utility.h"

#include <iostream>
#include <istream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace HighOrderCRF {

using std::cerr;
using std::endl;
using std::istream;
using std::move;
using std::ostream;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

DataSequence::DataSequence(vector<string> originalStringList,
                           vector<string> labels,
                           vector<unordered_set<string>> possibleLabelSetList,
                           vector<vector<FeatureTemplate>> featureTemplateListList) {
    this->originalStringList = move(originalStringList);
    this->labels = move(labels);
    this->possibleLabelSetList = move(possibleLabelSetList);
    this->featureTemplateListList = move(featureTemplateListList);
    if (labels.size() != this->featureTemplateListList.size() || labels.size() != this->possibleLabelSetList.size() || labels.size() != originalStringList.size()) {
        cerr << "Sizes does not match." << endl;
        exit(1);
    }
}

DataSequence::DataSequence(istream &is) {
    string line;
    bool isOK = false;
    while (getline(is, line)) {
        if (line.empty()) {
            isOK = true;
            break;
        }
        auto fields = splitString(line);
        if (fields.size() < 3) {
            cerr << "Not enough fields: " << line << endl;
            exit(1);
        }
        originalStringList.emplace_back(move(fields[0]));
        labels.emplace_back(move(fields[1]));
        if (fields[2] != "*") {
            auto possibleLabelList = splitString(fields[2], ',');
            unordered_set<string> possibleLabelSet(possibleLabelList.begin(),
                                                   possibleLabelList.end());
            possibleLabelSetList.emplace_back(move(possibleLabelSet));
        }
        vector<FeatureTemplate> featureTemplateList;
        for (size_t i = 3; i < fields.size(); ++i) {
            featureTemplateList.emplace_back(fields[i]);
        }
        featureTemplateListList.emplace_back(featureTemplateList);
    }
    if (!isOK) {
        originalStringList.clear();
        labels.clear();
        possibleLabelSetList.clear();
        featureTemplateListList.clear();
    }
}

void DataSequence::write(ostream &os) const {
    for (size_t i = 0; i < labels.size(); ++i) {
        os << originalStringList[i] << "\t"
           << labels[i] << "\t";
        if (possibleLabelSetList.empty()) {
            os << "*";
        }
        else {
            for (auto it = possibleLabelSetList[i].begin();
                 it != possibleLabelSetList[i].end();
                 ++it) {
                if (it != possibleLabelSetList[i].begin()) {
                    os << ",";
                }
                os << *it;
            }
        }
        for (const auto &ft : featureTemplateListList[i]) {
            os << "\t";
            os << ft.toString();
        }
        os << "\n";
    }
    os << endl;
}

InternalDataSequence DataSequence::toInternalDataSequence(const unordered_map<string, label_t> &labelMap) {
    vector<label_t> l;
    l.reserve(labels.size());
    for (const auto &str : labels) {
        l.emplace_back(labelMap.at(str));
    }
    
    vector<unordered_set<label_t>> p;
    p.reserve(possibleLabelSetList.size());
    for (const auto &labelSet : possibleLabelSetList) {
        unordered_set<label_t> s;
        for (const auto &str : labelSet) {
            s.insert(labelMap.at(str));
        }
        p.emplace_back(move(s));
    }
    
    return InternalDataSequence(l, p, move(featureTemplateListList));
}

const vector<string> &DataSequence::getLabels() const {
    return labels;
}

const vector<string> &DataSequence::getOriginalStringList() const {
    return originalStringList;
}

unordered_set<string> DataSequence::getUsedLabelSet() const {
    unordered_set<string> ret;
    for (const auto &l : labels) {
        ret.insert(l);
    }
    for (const auto &s : possibleLabelSetList) {
        ret.insert(s.begin(), s.end());
    }
    return ret;
}

size_t DataSequence::length() const {
    return featureTemplateListList.size();
}

bool DataSequence::empty() const {
    return length() == 0;
}

}  // namespace HighOrderCRF
