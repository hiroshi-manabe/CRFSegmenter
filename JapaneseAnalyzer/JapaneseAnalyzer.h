#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace DataConverter {
class DataConverterInterface;
}

namespace HighOrderCRF {
class HighOrderCRFProcessor;
}

namespace MorphemeDisambiguator {
class MorphemeDisambiguatorClass;
}

namespace JapaneseAnalyzer {

class JapaneseAnalyzer {
public:
    JapaneseAnalyzer(const std::unordered_set<std::string> &segmenterDicts,
                     const std::string &segmenterModel,
                     const std::unordered_set<std::string> &taggerDicts,
                     const std::string &taggerModel,
                     const std::unordered_set<std::string> &morphDicts,
                     const std::string &morphModel);
    std::vector<std::vector<std::string>> analyze(const std::string &line);
private:
    std::shared_ptr<DataConverter::DataConverterInterface> segmenterConverter;
    std::shared_ptr<HighOrderCRF::HighOrderCRFProcessor> segmenterProcessor;
    std::shared_ptr<DataConverter::DataConverterInterface> taggerConverter;
    std::shared_ptr<HighOrderCRF::HighOrderCRFProcessor> taggerProcessor;
    std::shared_ptr<MorphemeDisambiguator::MorphemeDisambiguatorClass> morphemeDisambiguator;
};

}  // namespace JapaneseAnalyzer
