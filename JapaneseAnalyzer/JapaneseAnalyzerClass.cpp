#include "JapaneseAnalyzerClass.h"

#include "../DataConverter/SegmenterDataConverter.h"
#include "../DataConverter/TaggerDataConverter.h"
#include "../HighOrderCRF/DataSequence.h"
#include "../HighOrderCRF/FeatureTemplate.h"
#include "../HighOrderCRF/HighOrderCRFProcessor.h"
#include "../MorphemeConcatenator/MorphemeConcatenatorClass.h"
#include "../MorphemeDisambiguator/MorphemeDisambiguatorOptions.h"
#include "../MorphemeDisambiguator/MorphemeDisambiguatorClass.h"
#include "../Utility/SegmenterUtil.h"
#include "../Utility/StringUtil.h"
#include "../Utility/UnicodeCharacter.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::for_each;
using std::make_shared;
using std::move;
using std::regex;
using std::sregex_token_iterator;
using std::string;
using std::transform;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using Utility::UnicodeCharacter;

namespace JapaneseAnalyzer {

vector<string> segment(const DataConverter::DataConverterInterface &segmenterConverter,
                       const HighOrderCRF::HighOrderCRFProcessor &segmenterProcessor,
                       const string &line) {
    string transformed;
    transform(line.begin(), line.end(), back_inserter(transformed), [](char c) { return c == '\t' ? ' ' : c; });
    auto origChars = UnicodeCharacter::stringToUnicodeCharacterList(transformed);
    origChars.emplace_back(0x3002);  // '。'
    auto segmenterInput = Utility::toSegmenterInput(origChars, true);
    auto dataSequence = segmenterConverter.toDataSequence(segmenterInput);
    auto segmenterOutput = segmenterProcessor.tag(dataSequence.get());
    vector<string> ret;
    string str;
    for (size_t i = 0; i < segmenterOutput.size(); ++i) {
        if ((i > 0 && segmenterOutput[i] == "1") || i == segmenterOutput.size() - 1) {
            ret.emplace_back(str);
            str.clear();
        }
        auto s = origChars[i].toString();
        str.append(s, s[0] == ' ' ? 1 : 0, string::npos);
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
        ret.emplace_back(input[i] + "/" + taggerOutput[i]);
    }
    return ret;
}

vector<vector<string>> morphTag(const MorphemeDisambiguator::MorphemeDisambiguatorClass &morphemeDisambiguator,
                                const vector<string> &input) {
    return morphemeDisambiguator.tag(input);
}

vector<vector<string>> concatenate(const MorphemeConcatenator::MorphemeConcatenatorClass &morphemeConcatenator,
                                   const vector<vector<string>> &input) {
    return morphemeConcatenator.concatenate(input);
}

JapaneseAnalyzerClass::JapaneseAnalyzerClass(const unordered_set<string> &segmenterDicts,
                                             const string &segmenterModel,
                                             const unordered_set<string> &taggerDicts,
                                             const string &taggerModel,
                                             const unordered_set<string> &morphDicts,
                                             const string &morphModel,
                                             const unordered_set<string> &concatDicts) {
    
    unordered_map<string, string> segmenterOptions{};
    unordered_map<string, string> taggerOptions{};
    MorphemeDisambiguator::MorphemeDisambiguatorOptions morphOptions{ 2, 1, 1, { 0, 3 }, morphDicts };
    segmenterConverter = make_shared<DataConverter::SegmenterDataConverter>(segmenterOptions, segmenterDicts);
    segmenterProcessor = make_shared<HighOrderCRF::HighOrderCRFProcessor>();
    segmenterProcessor->readModel(segmenterModel);
    taggerConverter = make_shared<DataConverter::TaggerDataConverter>(taggerOptions, taggerDicts);
    taggerProcessor = make_shared<HighOrderCRF::HighOrderCRFProcessor>();
    taggerProcessor->readModel(taggerModel);
    morphemeDisambiguator = make_shared<MorphemeDisambiguator::MorphemeDisambiguatorClass>(morphOptions);
    morphemeDisambiguator->readModel(morphModel);
    if (!concatDicts.empty()) {
        morphemeConcatenator = make_shared<MorphemeConcatenator::MorphemeConcatenatorClass>(concatDicts);
    }
}

vector<vector<string>> JapaneseAnalyzerClass::analyze(const string &line) const {
    vector<vector<string>> ret;
    if (line.empty()) {
        return ret;
    }
    auto segmented = segment(*segmenterConverter.get(), *segmenterProcessor.get(), line);
    auto tagged = tag(*taggerConverter.get(), *taggerProcessor.get(), segmented);
    auto morphTagged = morphTag(*morphemeDisambiguator.get(), tagged);
    if (morphemeConcatenator.get()) {
        ret = concatenate(*morphemeConcatenator.get(), morphTagged);
    }
    else {
        ret = move(morphTagged);
    }
    return ret;
}

}  // namespace JapaneseAnalyzer
