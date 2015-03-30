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

class UnicodeCharacter;

class CharacterFeatureGenerator : public FeatureTemplateGenerator<UnicodeCharacter> {
public:
    CharacterFeatureGenerator(size_t maxNgram, size_t maxWindow, size_t maxLabelLength);
    virtual shared_ptr<vector<shared_ptr<FeatureTemplate>>> generateFeatureTemplatesAt(shared_ptr<vector<UnicodeCharacter>> observationList, size_t pos) const;

private:
    size_t maxNgram;
    size_t maxWindow;
    size_t maxLabelLength;
};

}

#endif  // HOCRF_SEGMENTER_CHARACTER_FEATURE_GENERATOR_H_
