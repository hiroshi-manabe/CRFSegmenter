#ifndef HOCRF_HIGH_ORDER_CRF_OBSERVATION_SEQUENCE_H_
#define HOCRF_HIGH_ORDER_CRF_OBSERVATION_SEQUENCE_H_

#include "types.h"
#include "DataSequence.h"
#include "FeatureTemplateGenerator.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace HighOrderCRF {

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
        auto featureTemplateListList = make_shared<vector<shared_ptr<vector<shared_ptr<FeatureTemplate>>>>>();
        auto labels = make_shared<vector<label_t>>();
        featureTemplateListList->reserve(observationList->size());
        labels->reserve(observationList->size());
        auto possibleLabelTypeSetList = make_shared<vector<unordered_set<label_t>>>();
        
        for (size_t pos = 0; pos < observationList->size(); ++pos) {
            featureTemplateListList->push_back(featureTemplateGenerator->generateFeatureTemplatesAt(observationList, pos));
            labels->push_back(hasValidLabels ? labelMap->at(labelList->at(pos)) : 0);
            unordered_set<label_t> possibleLabelTypeSet;
            for (const auto &label : (*possibleLabelSetList)[pos]) {
                possibleLabelTypeSet.insert(labelMap->at(label));
            }
            possibleLabelTypeSetList->push_back(move(possibleLabelTypeSet));
        }
        return make_shared<DataSequence>(featureTemplateListList, labels, possibleLabelTypeSetList, hasValidLabels);
   }

    string generateCRFSuiteData(shared_ptr<FeatureTemplateGenerator<T>> featureTemplateGenerator) {
        string ret;
        for (size_t i = 0; i < observationList->size(); ++i) {
            ret += (*labelList)[i];
            auto templateList = featureTemplateGenerator->generateFeatureTemplatesAt(observationList, i);
            auto tempMap = unordered_map<string, bool>();
            for (auto &ft : *templateList) {
                auto &obs = ft->getObservation();
                if (tempMap.find(obs) == tempMap.end()) {
                    ret += "\t";
                    ret += (obs.empty() ? "LABEL" : obs);
                    tempMap.insert(make_pair(ft->getObservation(), true));
                }
            }
            ret += "\n";
        }
        ret += "__BOS_EOS__\n\n";
        return ret;
    }

private:
    shared_ptr<vector<T>> observationList;
    shared_ptr<vector<string>> labelList;
    shared_ptr<vector<unordered_set<string>>> possibleLabelSetList;
    bool hasValidLabels;
};

}  // namespace HighOrderCRF
#endif  // HOCRF_HIGH_ORDER_CRF_OBSERVATION_SEQUENCE_H_
