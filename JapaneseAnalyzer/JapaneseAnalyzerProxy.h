#include <string>
#include <set>
#include <vector>

namespace JapaneseAnalyzer {

class JapaneseAnalyzer;

class JapaneseAnalyzerProxy {
public:
    JapaneseAnalyzerProxy(const std::set<std::string> &segmenterDicts,
                          const std::string &segmenterModel,
                          const std::set<std::string> &taggerDicts,
                          const std::string &taggerModel,
                          const std::set<std::string> &morphDicts,
                          const std::string &morphModel);
    std::vector<std::vector<std::string> > analyze(const std::string &line);
    ~JapaneseAnalyzerProxy();
private:
    JapaneseAnalyzer *analyzer;
};

}  // namespace JapaneseAnalyzer
