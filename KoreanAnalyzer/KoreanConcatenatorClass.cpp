#include "KoreanConcatenatorClass.h"

#include "../DataConverter/SegmenterDataConverter.h"
#include "../HighOrderCRF/DataSequence.h"
#include "../HighOrderCRF/FeatureTemplate.h"
#include "../HighOrderCRF/HighOrderCRFProcessor.h"
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

using Utility::UnicodeCharacter;

namespace KoreanAnalyzer {

const string delim(u8"\ue100");

vector<string> toConcatenatorInput(const vector<UnicodeCharacter> &input) {
    vector<string> ret;
    
    for (size_t i = 0; i < input.size(); ++i) {
        auto &ch = input[i];
        bool nextIsSpace = i + 1 < input.size() ? input[i + 1].getCodePoint() == ' ' : false;
        string possibleLabelStr("0 1");
        
        if (nextIsSpace) {
            possibleLabelStr = "0 1";
            ++i;
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

string execute(const DataConverter::DataConverterInterface &concatenatorConverter,
                                const HighOrderCRF::HighOrderCRFProcessor &concatenatorProcessor,
                                const string &line) {
    string transformed;
    transform(line.begin(), line.end(), back_inserter(transformed), [](char c) { return c == '\t' ? ' ' : c; });
    auto origChars = UnicodeCharacter::stringToUnicodeCharacterList(line);
    vector<UnicodeCharacter> processedChars;
    for (const auto &ch : origChars) {
        auto chars = Utility::decomposeHangeul(ch);
        processedChars.insert(processedChars.end(), chars.begin(), chars.end());
    }
    auto concatenatorInput = toConcatenatorInput(processedChars);
    auto dataSequence = concatenatorConverter.toDataSequence(concatenatorInput);
    auto concatenatorOutput = concatenatorProcessor.tag(dataSequence.get());
    vector<UnicodeCharacter> resultChars;
    for (size_t i = 0; i < concatenatorOutput.size(); ++i) {
        resultChars.emplace_back(processedChars[i]);
    }
    string ret;
    size_t prev = 0;
    for (size_t i = 0; i <= concatenatorOutput.size(); ++i) {
        if (i == concatenatorOutput.size() || (i > 0 && concatenatorOutput[i] == "1")) {
            for (size_t j = prev; j < i; ++j) {
                if (j != prev && isPatchim(resultChars[j])) {
                    continue;
                }
                ret += recomposeHangeul(resultChars[j],
                    (j == concatenatorOutput.size() - 1 || concatenatorOutput[j + 1] == "1") ?
                    0 : resultChars[j + 1]).toString();
            }
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
    return execute(*concatenatorConverter.get(), *concatenatorProcessor.get(), line);
}

}  // namespace KoreanAnalyzer
