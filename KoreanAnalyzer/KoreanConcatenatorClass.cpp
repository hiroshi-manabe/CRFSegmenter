#include "KoreanConcatenatorClass.h"

#include "../DataConverter/SegmenterDataConverter.h"
#include "../HighOrderCRF/DataSequence.h"
#include "../HighOrderCRF/FeatureTemplate.h"
#include "../HighOrderCRF/HighOrderCRFProcessor.h"
#include "../Utility/CharWithSpace.h"
#include "../Utility/KoreanUtil.h"
#include "../Utility/StringUtil.h"
#include "../Utility/UnicodeCharacter.h"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::back_inserter;
using std::make_shared;
using std::move;
using std::string;
using std::to_string;
using std::transform;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using Utility::CharWithSpace;
using Utility::UnicodeCharacter;

namespace KoreanAnalyzer {

const string delim(u8"\ue100");

vector<string> toConcatenatorInput(const vector<CharWithSpace> &input) {
    vector<string> ret;
    
    for (const auto ch : input) {
        string possibleLabelStr("0 1");
        
        if (ch.hasSpace()) {
            possibleLabelStr = "0 1";
        }
        else {
            possibleLabelStr = "0";
        }
        ret.emplace_back(ch.toString() +
                         "\t" +
                         possibleLabelStr +
                         "\t" +
                         "*");
    }
    return ret;
}

struct StringWithSpace {
    string str;
    bool hasSpace;
    StringWithSpace(string str, bool hasSpace) : str(str), hasSpace(hasSpace) {};
};

vector<StringWithSpace> execute(const DataConverter::DataConverterInterface &concatenatorConverter,
                                const HighOrderCRF::HighOrderCRFProcessor &concatenatorProcessor,
                                const string &line) {
    string transformed;
    transform(line.begin(), line.end(), back_inserter(transformed), [](char c) { return c == '\t' ? ' ' : c; });
    auto origChars = CharWithSpace::stringToCharWithSpaceList(line);
    vector<CharWithSpace> processedChars;
    for (const auto &ch : origChars) {
        auto chars = Utility::decomposeHangeul(ch);
        processedChars.insert(processedChars.end(), chars.begin(), chars.end());
    }
    auto concatenatorInput = toConcatenatorInput(processedChars);
    auto dataSequence = concatenatorConverter.toDataSequence(concatenatorInput);
    auto concatenatorOutput = concatenatorProcessor.tag(dataSequence.get());
    vector<CharWithSpace> resultChars;
    for (size_t i = 0; i < concatenatorOutput.size(); ++i) {
        resultChars.emplace_back(processedChars[i].getUnicodeCharacter(), concatenatorOutput[i] == "1" ? true : false);
    }
    vector<StringWithSpace> ret;
    size_t prev = 0;
    for (size_t i = 0; i <= concatenatorOutput.size(); ++i) {
        if (i == concatenatorOutput.size() || (i > 0 && concatenatorOutput[i] == "1")) {
            string str;
            for (size_t j = prev; j < i; ++j) {
                if (j != prev && isPatchim(resultChars[j].getUnicodeCharacter())) {
                    continue;
                }
                str.append(recomposeHangeul(resultChars[j],
                    (j == concatenatorOutput.size() - 1 || concatenatorOutput[j + 1] == "1") ?
                    CharWithSpace(0, false) : resultChars[j + 1]).getUnicodeCharacter().toString());
            }
            ret.emplace_back(str, resultChars[prev].hasSpace());
            prev = i;
        }
    }
    return ret;
}

KoreanConcatenatorClass::KoreanConcatenatorClass(const unordered_set<string> &concatenatorDicts,
                                         const string &concatenatorModel,
                                         size_t concatenatorOrder) {
    unordered_map<string, string> concatenatorOptions {
        {"charMaxNgram", to_string(concatenatorOrder)},
        {"charMaxWindow", to_string(concatenatorOrder)},
        {"charMaxLabelLength", to_string(concatenatorOrder + 1)}
    };
    concatenatorConverter = make_shared<DataConverter::SegmenterDataConverter>(concatenatorOptions, concatenatorDicts);
    concatenatorProcessor = make_shared<HighOrderCRF::HighOrderCRFProcessor>();
    concatenatorProcessor->readModel(concatenatorModel);
}

string KoreanConcatenatorClass::concatenate(const string &line) const {
    if (line.empty()) {
        return "";
    }
    auto concatenated = execute(*concatenatorConverter.get(), *concatenatorProcessor.get(), line);
    vector<string> concatenatedStringList;
    transform(concatenated.begin(), concatenated.end(), back_inserter(concatenatedStringList), [](StringWithSpace s) { return s.str; });
    return Utility::join(concatenatedStringList, ' ');
}

}  // namespace KoreanAnalyzer
