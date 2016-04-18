#ifndef HOCRF_SEGMENTER_CHARACTER_FEATURE_GENERATOR_H_
#define HOCRF_SEGMENTER_CHARACTER_FEATURE_GENERATOR_H_

#include <memory>
#include <vector>

#include "../HighOrderCRF/FeatureTemplate.h"
#include "../HighOrderCRF/FeatureTemplateGenerator.h"

namespace Segmenter {

using std::shared_ptr;
using std::vector;

using HighOrderCRF::FeatureTemplate;
using HighOrderCRF::FeatureTemplateGenerator;

class CharWithSpace;

class CharacterFeatureGenerator : public FeatureTemplateGenerator<CharWithSpace> {
public:
    CharacterFeatureGenerator(size_t maxNgram, size_t maxWindow, size_t maxLabelLength);
    virtual shared_ptr<vector<vector<shared_ptr<FeatureTemplate>>>> generateFeatureTemplates(shared_ptr<vector<CharWithSpace>> observationList) const;

private:
    size_t maxNgram;
    size_t maxWindow;
    size_t maxLabelLength;
};

}

#endif  // HOCRF_SEGMENTER_CHARACTER_FEATURE_GENERATOR_H_
