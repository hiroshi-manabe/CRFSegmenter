#ifndef HOCRF_JAPANESE_ANALYZER_JAPANESE_ANALYZER_PROXY_H_
#define HOCRF_JAPANESE_ANALYZER_JAPANESE_ANALYZER_PROXY_H_

#include <string>
#include <set>
#include <vector>

namespace JapaneseAnalyzer {

class JapaneseAnalyzerClass;

class JapaneseAnalyzerProxy {
public:
    JapaneseAnalyzerProxy(const std::set<std::string> &segmenterDicts,
                          const std::string &segmenterModel,
                          const std::set<std::string> &taggerDicts,
                          const std::string &taggerModel,
                          const std::set<std::string> &morphDicts,
                          const std::string &morphModel,
                          const std::set<std::string> &concatDicts);
    std::vector<std::vector<std::string> > analyze(const std::string &line) const;
    ~JapaneseAnalyzerProxy();
private:
    JapaneseAnalyzerClass *analyzer;
};

}  // namespace JapaneseAnalyzer

#endif  // HOCRF_JAPANESE_ANALYZER_JAPANESE_ANALYZER_PROXY_H_
