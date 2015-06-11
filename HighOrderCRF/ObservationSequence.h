#ifndef HOCRF_HIGH_ORDER_CRF_OBSERVATION_SEQUENCE_H_
#define HOCRF_HIGH_ORDER_CRF_OBSERVATION_SEQUENCE_H_

#include "types.h"
#include "DataSequence.h"
#include "FeatureTemplateGenerator.h"

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace HighOrderCRF {

using std::cerr;
using std::endl;
using std::make_pair;
using std::make_shared;
using std::move;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

template<typename T> class ObservationSequence
{
public:
    ObservationSequence(shared_ptr<vector<T>> observationList, shared_ptr<vector<string>> labelList, shared_ptr<vector<unordered_set<string>>> possibleLabelSetList, bool hasValidLabels) {
        this->observationList = observationList;
        this->labelList = labelList;
        this->possibleLabelSetList = possibleLabelSetList;
        this->hasValidLabels = hasValidLabels;
    }

    shared_ptr<vector<T>> getObservationList() {
        return observationList;
    }

    shared_ptr<vector<string>> getLabelList() {
        return labelList;
    }

    shared_ptr<vector<unordered_set<string>>> getPossibleLabelSetList() {
        return possibleLabelSetList;
    }

    shared_ptr<DataSequence> generateDataSequence(shared_ptr<FeatureTemplateGenerator<T>> featureTemplateGenerator,
        shared_ptr<unordered_map<string, label_t>> labelMap) {
        auto labels = make_shared<vector<label_t>>();
        labels->reserve(observationList->size());
        auto possibleLabelTypeSetList = make_shared<vector<unordered_set<label_t>>>();
        auto featureTemplateListList = featureTemplateGenerator->generateFeatureTemplates(observationList);
        for (size_t pos = 0; pos < observationList->size(); ++pos) {
            if (hasValidLabels && labelMap->find(labelList->at(pos)) == labelMap->end()) {
                cerr << "Unknown label: " << labelList->at(pos) << endl;
                exit(1);
            }
            labels->push_back(hasValidLabels ? labelMap->at(labelList->at(pos)) : 0);
            unordered_set<label_t> possibleLabelTypeSet;
            for (const auto &label : (*possibleLabelSetList)[pos]) {
                if (labelMap->find(label) == labelMap->end()) {
                    cerr << "Unknown label: " << label << endl;
                }
                possibleLabelTypeSet.insert(labelMap->at(label));
            }
            possibleLabelTypeSetList->push_back(move(possibleLabelTypeSet));
        }
        return make_shared<DataSequence>(featureTemplateListList, labels, possibleLabelTypeSetList, hasValidLabels);
   }

private:
    shared_ptr<vector<T>> observationList;
    shared_ptr<vector<string>> labelList;
    shared_ptr<vector<unordered_set<string>>> possibleLabelSetList;
    bool hasValidLabels;
};

}  // namespace HighOrderCRF
#endif  // HOCRF_HIGH_ORDER_CRF_OBSERVATION_SEQUENCE_H_
