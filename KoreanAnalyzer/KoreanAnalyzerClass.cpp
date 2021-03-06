#include "KoreanAnalyzerClass.h"

#include "../DataConverter/SegmenterDataConverter.h"
#include "../DataConverter/TaggerDataConverter.h"
#include "../HighOrderCRF/DataSequence.h"
#include "../HighOrderCRF/FeatureTemplate.h"
#include "../HighOrderCRF/HighOrderCRFProcessor.h"
#include "../NgramDecoder/NgramDictionaryDecoder.h"
#include "../Utility/KoreanUtil.h"
#include "../Utility/SegmenterUtil.h"
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
using std::to_string;
using std::transform;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using Utility::UnicodeCharacter;

namespace KoreanAnalyzer {

const string delim(u8"\ue100");

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
    auto origChars = UnicodeCharacter::stringToUnicodeCharacterList(transformed);
    vector<UnicodeCharacter> processedChars;
    for (const auto &ch : origChars) {
        auto chars = Utility::decomposeHangeul(ch);
        processedChars.insert(processedChars.end(), chars.begin(), chars.end());
    }
    auto segmenterInput = Utility::toSegmenterInput(processedChars);
    auto dataSequence = segmenterConverter.toDataSequence(segmenterInput);
    auto segmenterOutput = segmenterProcessor.tag(dataSequence.get());
    vector<StringWithSpace> ret;
    size_t prev = 0;
    size_t indexProcessedChars = 0;
    bool prevHasSpace = false;
    for (size_t i = 0; i <= segmenterOutput.size(); ++i) {
        if (i == segmenterOutput.size() || (i > 0 && segmenterOutput[i] == "1")) {
            string str;
            int diff = indexProcessedChars - prev;
            for (size_t j = prev; j < i; ++j) {
                if (j != prev && Utility::isPatchim(processedChars[j + diff])) {
                    continue;
                }
                str.append(Utility::recomposeHangeul(processedChars[j + diff],
                    (j == segmenterOutput.size() - 1 || segmenterOutput[j + 1] == "1") ?
                    UnicodeCharacter(0) : processedChars[j + diff + 1]).toString());
            }
            ret.emplace_back(move(str), prevHasSpace);
            prevHasSpace = false;
            indexProcessedChars += i - prev;
            if (indexProcessedChars < processedChars.size() && processedChars[indexProcessedChars].getCodePoint() == ' ' && indexProcessedChars < processedChars.size() - 1) {
                prevHasSpace = true;
                ++indexProcessedChars;
            }
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

vector<vector<string>> ngramDecode(const NgramDecoder::NgramDictionaryDecoder &dictionaryDecoder,
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
            fields.push_back(fields[0]);
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
    dictionaryDecoder = make_shared<NgramDecoder::NgramDictionaryDecoder>(ngramModel, ngramDicts);
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
