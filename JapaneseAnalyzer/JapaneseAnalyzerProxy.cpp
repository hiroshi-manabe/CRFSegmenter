#include "JapaneseAnalyzerProxy.h"

#include "JapaneseAnalyzer.h"

#include <string>
#include <set>
#include <unordered_set>
#include <vector>

using std::set;
using std::string;
using std::unordered_set;
using std::vector;

namespace JapaneseAnalyzer {

JapaneseAnalyzerProxy::JapaneseAnalyzerProxy(const set<string> &segmenterDicts,
                                             const string &segmenterModel,
                                             const set<string> &taggerDicts,
                                             const string &taggerModel,
                                             const set<string> &morphDicts,
                                             const string &morphModel) {
    unordered_set<string> sd(segmenterDicts.begin(), segmenterDicts.end());
    unordered_set<string> td(taggerDicts.begin(), taggerDicts.end());
    unordered_set<string> md(morphDicts.begin(), morphDicts.end());
    analyzer = new JapaneseAnalyzer(sd,
                                    segmenterModel,
                                    td,
                                    taggerModel,
                                    md,
                                    morphModel);
}

JapaneseAnalyzerProxy::~JapaneseAnalyzerProxy() {
    delete analyzer;
}

vector<vector<string>> JapaneseAnalyzerProxy::analyze(const string &line) {
    return analyzer->analyze(line);
}

}  // namespace JapaneseAnalyzer
