#include <algorithm>
#include <cassert>
#include <future>
#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#include "../DataConverter/SegmenterDataConverter.h"
#include "../DataConverter/TaggerDataConverter.h"
#include "../HighOrderCRF/FeatureTemplate.h"
#include "../HighOrderCRF/HighOrderCRFProcessor.h"
#include "../MorphemeDisambiguator/MorphemeDisambiguatorOptions.h"
#include "../MorphemeDisambiguator/MorphemeDisambiguatorClass.h"
#include "../Utility/StringUtil.h"
#include "../Utility/UnicodeCharacter.h"

namespace JapaneseAnalyzer {

class JapaneseAnalyzer {
public:
    JapaneseAnalyzer(const std::string &segmenterDict,
                     const std::string &segmenterModel,
                     const std::string &taggerDict,
                     const std::string &taggerModel,
                     const std::string &morphDict,
                     const std::string &morphModel);
    std::vector<std::vector<std::string>> analyze(const std::string line);
private:
    std::shared_ptr<DataConverter::DataConverterInterface> segmenterConverter;
    std::shared_ptr<HighOrderCRF::HighOrderCRFProcessor> segmenterProcessor;
    std::shared_ptr<DataConverter::DataConverterInterface> taggerConverter;
    std::shared_ptr<HighOrderCRF::HighOrderCRFProcessor> taggerProcessor;
    std::shared_ptr<MorphemeDisambiguator::MorphemeDisambiguatorClass> morphemeDisambiguator;
};

}  // namespace JapaneseAnalyzer
