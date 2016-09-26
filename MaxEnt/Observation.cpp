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
#include <utility>
#include <vector>

namespace MaxEnt {

using std::endl;
using std::make_pair;
using std::make_shared;
using std::move;
using std::ostream;
using std::pair;
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

shared_ptr<CompiledData> Observation::compile(unordered_map<string, uint32_t> *labelToIndexMap, unordered_map<string, uint32_t> *attrToIndexMap, unordered_map<pair<uint32_t, uint32_t>, uint32_t> *indexPairToFeatureIndexMap, bool extendMaps) const {
    vector<vector<uint32_t>> featureIndexListList;
    vector<string> labelStringList;
    
    uint32_t index = 0;
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
        vector<uint32_t> v;
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
        featureIndexListList.push_back(vector<uint32_t>());
    }
    return make_shared<CompiledData>(move(featureIndexListList), move(labelStringList), correctLabelIndex);
}

}  // namespace MaxEnt
