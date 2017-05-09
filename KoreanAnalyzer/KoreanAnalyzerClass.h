#ifndef HOCRF_KOREAN_ANALYZER_KOREAN_ANALYZER_CLASS_H_
#define HOCRF_KOREAN_ANALYZER_KOREAN_ANALYZER_CLASS_H_

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

namespace NgramDecoder {
class DictionaryDecoder;
}

namespace KoreanAnalyzer {

class KoreanAnalyzerClass {
public:
    KoreanAnalyzerClass(const std::unordered_set<std::string> &segmenterDicts,
                        const std::string &segmenterModel,
                        const std::unordered_set<std::string> &taggerDicts,
                        const std::string &taggerModel,
                        const std::unordered_set<std::string> &ngramDicts,
                        const std::string &ngramModel);
    std::vector<std::vector<std::string>> analyze(const std::string &line) const;
private:
    std::shared_ptr<DataConverter::DataConverterInterface> segmenterConverter;
    std::shared_ptr<HighOrderCRF::HighOrderCRFProcessor> segmenterProcessor;
    std::shared_ptr<DataConverter::DataConverterInterface> taggerConverter;
    std::shared_ptr<HighOrderCRF::HighOrderCRFProcessor> taggerProcessor;
    std::shared_ptr<NgramDecoder::DictionaryDecoder> dictionaryDecoder;
};

}  // namespace KoreanAnalyzer

#endif  // HOCRF_KOREAN_ANALYZER_KOREAN_ANALYZER_CLASS_H_
