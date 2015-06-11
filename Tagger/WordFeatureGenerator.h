#ifndef HOCRF_TAGGER_WORD_FEATURE_GENERATOR_H_
#define HOCRF_TAGGER_WORD_FEATURE_GENERATOR_H_

#include <memory>
#include <string>
#include <vector>

#include "../HighOrderCRF/FeatureTemplate.h"
#include "../HighOrderCRF/FeatureTemplateGenerator.h"

namespace Tagger {

using std::shared_ptr;
using std::string;
using std::vector;

using HighOrderCRF::FeatureTemplate;
using HighOrderCRF::FeatureTemplateGenerator;

class WordFeatureGenerator : public FeatureTemplateGenerator<string> {
public:
    WordFeatureGenerator(size_t maxNgram, size_t maxWindow, size_t maxLabelLength);
    virtual shared_ptr<vector<vector<shared_ptr<FeatureTemplate>>>> generateFeatureTemplates(shared_ptr<vector<string>> observationList) const;

private:
    size_t maxNgram;
    size_t maxWindow;
    size_t maxLabelLength;
};

}

#endif  // HOCRF_TAGGER_WORD_FEATURE_GENERATOR_H_
