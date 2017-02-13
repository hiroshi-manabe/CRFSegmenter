#include "JapaneseAnalyzerProxy.h"

#include "JapaneseAnalyzerClass.h"

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
                                             const string &morphModel,
                                             const set<string> &concatDicts) {
    unordered_set<string> sd(segmenterDicts.begin(), segmenterDicts.end());
    unordered_set<string> td(taggerDicts.begin(), taggerDicts.end());
    unordered_set<string> md(morphDicts.begin(), morphDicts.end());
    unordered_set<string> cd(concatDicts.begin(), concatDicts.end());
    analyzer = new JapaneseAnalyzerClass(sd,
                                         segmenterModel,
                                         td,
                                         taggerModel,
                                         md,
                                         morphModel,
                                         cd);
}

JapaneseAnalyzerProxy::~JapaneseAnalyzerProxy() {
    delete analyzer;
}

vector<vector<string>> JapaneseAnalyzerProxy::analyze(const string &line) const {
    return analyzer->analyze(line);
}

}  // namespace JapaneseAnalyzer
