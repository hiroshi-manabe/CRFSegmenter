#ifndef HOCRF_OBSERVATION_SET_H_
#define HOCRF_OBSERVATION_SET_H_

#include "types.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace HighOrderCRF {

using std::make_shared;
using std::pair;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

template<typename T> class ObservationSequence;

template<typename T> class ObservationSet
{
public:
    ObservationSet(shared_ptr<vector<shared_ptr<ObservationSequence<T>>> const> observationSequenceList) {
        this->observationSequenceList = observationSequenceList;
    }
    shared_ptr<unordered_map<string, label_t>> generateLabelMap() {
        auto labelMap = make_shared<unordered_map<string, label_t>>();
        for (auto &seq : *observationSequenceList) {
            auto labelList = seq->getLabelList();
            for (auto &label : *labelList) {
                if (labelMap->find(label) == labelMap->end()) {
                    labelMap->insert(pair<string, label_t>(label, labelMap->size()));
                }
            }
        }
        return labelMap;
    }
    
private:
    shared_ptr<vector<shared_ptr<ObservationSequence<T>>> const> observationSequenceList;
};

}  // namespace HighOrderCRF
#endif  // HOCRF_OBSERVATION_SET_H_
