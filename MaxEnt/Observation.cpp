#include "CompiledData.h"
#include "Observation.h"

#include <cmath>
#include <memory>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace MaxEnt {

using std::endl;
using std::make_pair;
using std::make_shared;
using std::move;
using std::ostream;
using std::set;
using std::shared_ptr;
using std::stringstream;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

Observation::Observation(unordered_set<string> attributeSet, string correctLabel, set<string> possibleLabelSet) {
    this->attributeSet = attributeSet;
    this->correctLabel = correctLabel;
    this->possibleLabelSet = possibleLabelSet;
}

void Observation::output(ostream &os) {
    os << "possible labels:";
    for (auto possibleLabel : possibleLabelSet) {
        os << " " << possibleLabel;
    }
    os << endl;
    os << "correct label: " << correctLabel << endl;
    os << "attributes:";
    for (auto attr : attributeSet) {
        os << " " << attr;
    }
    os << endl << endl;
}

shared_ptr<CompiledData> Observation::compile(shared_ptr<unordered_map<string, size_t>> labelToIndexMap, shared_ptr<unordered_map<string, size_t>> attrToIndexMap, shared_ptr<unordered_map<pair<size_t, size_t>, size_t>> indexPairToFeatureIndexMap, bool extendMaps) const {
    vector<vector<size_t>> featureIndexListList;
    vector<string> labelStringList;
    
    size_t index = 0;
    size_t correctLabelIndex = 0;
    stringstream ss;

    bool isFirst = true;
    for (const auto &label : possibleLabelSet) {
        if (!isFirst) {
            ss << ":";
        }
        ss << label;
        isFirst = false;
    }
    string setStr = ss.str();
    for (const auto &label : possibleLabelSet) {
        if (!correctLabel.empty() && label == correctLabel) {
            correctLabelIndex = index;
        }
        vector<size_t> v;
        string labelAndLabelSetStr = label + "/" + setStr;
        auto itLabel = labelToIndexMap->find(labelAndLabelSetStr);
        if (itLabel == labelToIndexMap->end()) {
            if (!extendMaps) {
                continue; // FIXME
            }
            itLabel = labelToIndexMap->insert(make_pair(labelAndLabelSetStr, labelToIndexMap->size())).first;
        }
        labelStringList.push_back(label);
        for (const auto &attr : attributeSet) {
            auto itAttr = attrToIndexMap->find(attr);
            if (itAttr == attrToIndexMap->end()) {
                if (!extendMaps) {
                    continue;
                }
                itAttr = attrToIndexMap->insert(make_pair(attr, attrToIndexMap->size())).first;
            }
            auto indexPair = make_pair(itLabel->second, itAttr->second);
            auto itIndexPair = indexPairToFeatureIndexMap->find(indexPair);
            if (itIndexPair == indexPairToFeatureIndexMap->end()) {
                if (!extendMaps) {
                    continue;
                }
                itIndexPair = indexPairToFeatureIndexMap->insert(make_pair(indexPair, indexPairToFeatureIndexMap->size())).first;
            }
            v.push_back(itIndexPair->second);
        }
        featureIndexListList.push_back(move(v));
        ++index;
    }
    if (labelStringList.empty()) {
        labelStringList.push_back(*(possibleLabelSet.begin()));
        featureIndexListList.push_back(vector<size_t>());
    }
    return make_shared<CompiledData>(move(featureIndexListList), move(labelStringList), correctLabelIndex);
}

}  // namespace MaxEnt
