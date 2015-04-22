#include "CompiledData.h"
#include "Observation.h"

#include <cmath>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace MaxEnt {

using std::make_pair;
using std::make_shared;
using std::move;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

Observation::Observation(unordered_set<string> attributeSet, string correctLabel, unordered_set<string> possibleLabelSet) {
    this->attributeSet = attributeSet;
    this->correctLabel = correctLabel;
    this->possibleLabelSet = possibleLabelSet;
}

shared_ptr<CompiledData> Observation::compile(shared_ptr<unordered_map<string, size_t>> strToIndexMap, bool extendMap) const {
    vector<vector<size_t>> featureIndexListList;
    vector<string> labelStringList;
    
    size_t index = 0;
    size_t correctLabelIndex = 0;
    for (const auto &label : possibleLabelSet) {
        labelStringList.push_back(label);
        if (!correctLabel.empty() && label == correctLabel) {
            correctLabelIndex = index;
        }
        vector<size_t> v;
        for (const auto &attr : attributeSet) {
            string labelAndAttr = label + "\t" + attr;
            auto it = strToIndexMap->find(labelAndAttr);
            if (it == strToIndexMap->end()) {
                if (!extendMap) {
                    continue;
                }
                it = strToIndexMap->insert(make_pair(labelAndAttr, strToIndexMap->size())).first;
            }
            v.push_back(it->second);
        }
        featureIndexListList.push_back(move(v));
        ++index;
    }
    return make_shared<CompiledData>(move(featureIndexListList), move(labelStringList), correctLabelIndex);
}

}  // namespace MaxEnt
