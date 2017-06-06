#ifndef HOCRF_KOREAN_ANALYZER_KOREAN_CONCATENATOR_CLASS_H_
#define HOCRF_KOREAN_ANALYZER_KOREAN_CONCATENATOR_CLASS_H_

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

namespace KoreanAnalyzer {

class KoreanConcatenatorClass {
public:
    KoreanConcatenatorClass(const std::unordered_set<std::string> &concatenatorDicts,
                            const std::string &concatenatorModel,
                            size_t concatenatorOrder);
    std::string concatenate(const std::string &line) const;
private:
    std::shared_ptr<DataConverter::DataConverterInterface> concatenatorConverter;
    std::shared_ptr<HighOrderCRF::HighOrderCRFProcessor> concatenatorProcessor;
};

}  // namespace KoreanAnalyzer

#endif  // HOCRF_KOREAN_ANALYZER_KOREAN_CONCATENATOR_CLASS_H_
