#include "KoreanAnalyzerClass.h"

#include "../DataConverter/SegmenterDataConverter.h"
#include "../DataConverter/TaggerDataConverter.h"
#include "../HighOrderCRF/DataSequence.h"
#include "../HighOrderCRF/FeatureTemplate.h"
#include "../HighOrderCRF/HighOrderCRFProcessor.h"
#include "../NgramDecoder/DictionaryDecoder.h"
#include "../Utility/CharWithSpace.h"
#include "../Utility/StringUtil.h"
#include "../Utility/UnicodeCharacter.h"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::back_inserter;
using std::make_shared;
using std::move;
using std::string;
using std::transform;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using Utility::CharWithSpace;
using Utility::UnicodeCharacter;

namespace KoreanAnalyzer {

const string delim(u8"\ue100");

bool isHangeul(UnicodeCharacter ch) {
    return ch.getCodePoint() >= 0xac00 && ch.getCodePoint() <= 0xd7a3;
}

bool isPatchim(UnicodeCharacter ch) {
    return ch.getCodePoint() >= 0xe000 && ch.getCodePoint() <= 0xe01f;
}

vector<CharWithSpace> decomposeHangeul(CharWithSpace ch) {
    vector<CharWithSpace> ret{ ch };
    if (!isHangeul(ch.getUnicodeCharacter())) {
        return ret;
    }
    uint32_t code = ch.getUnicodeCharacter().getCodePoint();
    uint32_t patchimCode = (code - 0xac00) % 28;
    if (patchimCode == 4 ||
        patchimCode == 8 ||
        patchimCode == 16 ||
        patchimCode == 17 ||
        patchimCode == 20) {
        ret = { { code - patchimCode, ch.hasSpace() }, { 0xe000 + patchimCode, false } };
    }
    else if (patchimCode == 10) {
        ret = { {code - 2, ch.hasSpace()}, { 0xe000 + 16, false } };
    }
    return ret;
}

CharWithSpace recomposeHangeul(CharWithSpace input, CharWithSpace next) {
    CharWithSpace ret(input);
    if (next.hasSpace() || !isHangeul(input.getUnicodeCharacter()) || !isPatchim(next.getUnicodeCharacter())) {
        return ret;
    }
    uint32_t code = input.getUnicodeCharacter().getCodePoint();
    uint32_t patchimCode = (code - 0xac00) % 28;
    uint32_t newPatchimCode = next.getUnicodeCharacter().getCodePoint() - 0xe000;
    if (patchimCode == 0) {
        return{ code + newPatchimCode, input.hasSpace() };
    }
    else if (patchimCode == 8 && newPatchimCode == 16) {
        return{ code + 2, input.hasSpace() };
    }
    return ret;
}

vector<string> toSegmenterInput(const vector<CharWithSpace> &input) {
    vector<string> ret;
    
    for (const auto ch : input) {
        string possibleLabelStr("0 1");
        
        if (ch.hasSpace()) {
            possibleLabelStr = "1";
        }
        else {
            possibleLabelStr = "0 1";
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

vector<StringWithSpace> segment(const DataConverter::DataConverterInterface &segmenterConverter,
                                const HighOrderCRF::HighOrderCRFProcessor &segmenterProcessor,
                                const string &line) {
    string transformed;
    transform(line.begin(), line.end(), back_inserter(transformed), [](char c) { return c == '\t' ? ' ' : c; });
    auto origChars = CharWithSpace::stringToCharWithSpaceList(line);
    vector<CharWithSpace> processedChars;
    for (const auto &ch : origChars) {
        auto chars = decomposeHangeul(ch);
        processedChars.insert(processedChars.end(), chars.begin(), chars.end());
    }
    auto segmenterInput = toSegmenterInput(processedChars);
    auto dataSequence = segmenterConverter.toDataSequence(segmenterInput);
    auto segmenterOutput = segmenterProcessor.tag(dataSequence.get());
    vector<StringWithSpace> ret;
    size_t prev = 0;
    for (size_t i = 0; i <= segmenterOutput.size(); ++i) {
        if (i == segmenterOutput.size() || (i > 0 && segmenterOutput[i] == "1")) {
            string str;
            for (size_t j = prev; j < i; ++j) {
                if (j != prev && isPatchim(processedChars[j].getUnicodeCharacter())) {
                    continue;
                }
                str.append(recomposeHangeul(processedChars[j],
                    (j == segmenterOutput.size() - 1 || segmenterOutput[j + 1] == "1") ?
                    CharWithSpace(0, false) : processedChars[j + 1]).getUnicodeCharacter().toString());
            }
            ret.emplace_back(str, processedChars[prev].hasSpace());
            prev = i;
        }
    }
    return ret;
}

vector<string> tag(const DataConverter::DataConverterInterface &taggerConverter,
                   const HighOrderCRF::HighOrderCRFProcessor &taggerProcessor,
                   const vector<string> &input) {
    auto dataSequence = taggerConverter.toDataSequence(input);
    auto taggerOutput = taggerProcessor.tag(dataSequence.get());
    vector<string> ret;
    for (size_t i = 0; i < input.size(); ++i) {
        ret.emplace_back(input[i] + delim + taggerOutput[i]);
    }
    return ret;
}

vector<vector<string>> ngramDecode(const NgramDecoder::DictionaryDecoder &dictionaryDecoder,
                                   const vector<string> &input) {
    auto decoded = dictionaryDecoder.decode(input);
    vector<vector<string>> ret;
    for (auto str : decoded) {
        vector<string> fields;
        size_t pos = 0;
        while ((pos = str.find(delim)) != string::npos) {
            fields.emplace_back(str.substr(0, pos));
            str.erase(0, pos + delim.size());
        }
        fields.emplace_back(str);
        if (fields.size() == 2) {
            fields.emplace_back(fields[0]);
        }
        ret.emplace_back(move(fields));
    }
    return ret;
}

KoreanAnalyzerClass::KoreanAnalyzerClass(const unordered_set<string> &segmenterDicts,
                                         const string &segmenterModel,
                                         const unordered_set<string> &taggerDicts,
                                         const string &taggerModel,
                                         const unordered_set<string> &ngramDicts,
                                         const string &ngramModel) {
    unordered_map<string, string> segmenterOptions{};
    unordered_map<string, string> taggerOptions{};
    segmenterConverter = make_shared<DataConverter::SegmenterDataConverter>(segmenterOptions, segmenterDicts);
    segmenterProcessor = make_shared<HighOrderCRF::HighOrderCRFProcessor>();
    segmenterProcessor->readModel(segmenterModel);
    taggerConverter = make_shared<DataConverter::TaggerDataConverter>(taggerOptions, taggerDicts);
    taggerProcessor = make_shared<HighOrderCRF::HighOrderCRFProcessor>();
    taggerProcessor->readModel(taggerModel);
    dictionaryDecoder = make_shared<NgramDecoder::DictionaryDecoder>(ngramModel, ngramDicts);
}

vector<vector<string>> KoreanAnalyzerClass::analyze(const string &line) const {
    vector<vector<string>> ret;
    if (line.empty()) {
        return ret;
    }
    auto segmented = segment(*segmenterConverter.get(), *segmenterProcessor.get(), line);
    vector<string> segmentedStringList;
    transform(segmented.begin(), segmented.end(), back_inserter(segmentedStringList), [](StringWithSpace s) { return s.str; });
    auto tagged = tag(*taggerConverter.get(), *taggerProcessor.get(), segmentedStringList);
    ret = ngramDecode(*dictionaryDecoder.get(), tagged);
    for (size_t i = 0; i < ret.size(); ++i) {
        ret[i].emplace_back(segmented[i].hasSpace ? "1" : "0");
    }
    return ret;
}

}  // namespace KoreanAnalyzer