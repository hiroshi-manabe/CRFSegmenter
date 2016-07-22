#ifndef HOCRF_DATA_CONVERTER_OBSERVATION_SEQUENCE_H_
#define HOCRF_DATA_CONVERTER_OBSERVATION_SEQUENCE_H_

#include <sstream>
#include <unordered_set>
#include <utility>
#include <vector>

#include "FeatureTemplateGenerator.h"

namespace DataConverter {

template<typename T> class ObservationSequence
{
public:
    ObservationSequence(std::vector<T> observationList, std::vector<std::string> labelList, std::vector<std::unordered_set<std::string>> possibleLabelSetList) {
        this->observationList = std::move(observationList);
        this->labelList = std::move(labelList);
        this->possibleLabelSetList = std::move(possibleLabelSetList);
    }

    const std::vector<T> &getObservationListRef() const {
        return observationList;
    }

    const std::vector<std::string> &getLabelListRef() const {
        return labelList;
    }

    const std::vector<std::unordered_set<std::string>> getPossibleLabelSetListRef() {
        return possibleLabelSetList;
    }

    std::vector<std::string> generateSequence(std::shared_ptr<FeatureTemplateGenerator<T>> featureTemplateGenerator) {
        auto featureTemplateListList = featureTemplateGenerator->generateFeatureTemplates(observationList);
        std::vector<std::string> ret;
        ret.reserve(observationList.size());

        for (size_t pos = 0; pos < observationList.size(); ++pos) {
            stringstream ss;

            const auto &possibleLabelSet = possibleLabelSetList[pos];
            if (possibleLabelSet.empty()) {
                ss << "*";
            }
            else {
                bool isFirst = true;
                for (const auto &possibleLabel : possibleLabelSet) {
                    if (!isFirst) {
                        ss << ",";
                    }
                    ss << possibleLabel;
                    isFirst = false;
                }
            }
            ss << "\t";
            
            ss << labelList[pos];
            ss << "\t";

            bool isFirst = true;
            for (const auto featureTemplate : featureTemplateListList[pos]) {
                if (!isFirst) {
                    ss << "\t";
                }
                ss << featureTemplate.getLabelLength();
                ss << ":";
                ss << featureTemplate.getTag();
                isFirst = false;
            }
            ret.emplace_back(ss.str());
        }
        return ret;
   }

private:
    std::vector<T> observationList;
    std::vector<std::string> labelList;
    std::vector<std::unordered_set<std::string>> possibleLabelSetList;
};

}  // namespace DataConverter
#endif  // HOCRF_DATA_CONVERTER_OBSERVATION_SEQUENCE_H_
