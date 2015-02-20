#ifndef HOCRF_OBSERVATION_SEQUENCE_H_
#define HOCRF_OBSERVATION_SEQUENCE_H_

#include "types.h"
#include "DataSequence.h"
#include "FeatureTemplateGenerator.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace HighOrderCRF {

using std::make_shared;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

template<typename T> class ObservationSequence
{
public:
    ObservationSequence(shared_ptr<vector<T>> observationList, shared_ptr<vector<string>> labelList, bool hasValidLabels) {
        this->observationList = observationList;
        this->labelList = labelList;
        this->hasValidLabels = hasValidLabels;
    }

    shared_ptr<vector<T>> getObservationList() {
        return observationList;
    }

    shared_ptr<vector<string>> getLabelList() {
        return labelList;
    }

    shared_ptr<DataSequence> generateDataSequence(shared_ptr<FeatureTemplateGenerator<T>> featureTemplateGenerator,
        shared_ptr<unordered_map<string, label_t>> labelMap) {
        auto featureTemplateListList = make_shared<vector<shared_ptr<vector<shared_ptr<FeatureTemplate>>>>>();
        auto labels = make_shared<vector<label_t>>();
        for (size_t pos = 0; pos < observationList->size(); ++pos) {
            featureTemplateListList->push_back(featureTemplateGenerator->generateFeatureTemplatesAt(observationList, pos));
            labels->push_back(hasValidLabels ? labelMap->at(labelList->at(pos)) : 0);
        }
        return make_shared<DataSequence>(featureTemplateListList, labels, hasValidLabels);
    }

private:
    shared_ptr<vector<T>> observationList;
    shared_ptr<vector<string>> labelList;
    bool hasValidLabels;
};

}  // namespace HighOrderCRF
#endif  // HOCRF_OBSERVATION_SEQUENCE_H_
