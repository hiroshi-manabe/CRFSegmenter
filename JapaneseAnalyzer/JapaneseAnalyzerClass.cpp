#include "JapaneseAnalyzerClass.h"

#include "../DataConverter/SegmenterDataConverter.h"
#include "../DataConverter/TaggerDataConverter.h"
#include "../HighOrderCRF/DataSequence.h"
#include "../HighOrderCRF/FeatureTemplate.h"
#include "../HighOrderCRF/HighOrderCRFProcessor.h"
#include "../MorphemeConcatenator/MorphemeConcatenatorClass.h"
#include "../MorphemeDisambiguator/MorphemeDisambiguatorOptions.h"
#include "../MorphemeDisambiguator/MorphemeDisambiguatorClass.h"
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

using std::copy;
using std::for_each;
using std::make_shared;
using std::regex;
using std::sregex_token_iterator;
using std::string;
using std::transform;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using Utility::UnicodeCharacter;

namespace JapaneseAnalyzer {

vector<UnicodeCharacter> toUnicodeCharacterList(const string &orig) {
    vector<UnicodeCharacter> ret;
    for (auto it = orig.begin(); it != orig.end(); ) {
        size_t charCount;
        ret.emplace_back(UnicodeCharacter::fromString(it, orig.end() - it, &charCount));
        it += charCount;
    }
    return ret;
}

string toString(const vector<UnicodeCharacter> &origChars) {
    string ret;
    for (const auto c : origChars) {
        ret += c.toString();
    }
    return ret;
}

vector<UnicodeCharacter> toHankaku(const vector<UnicodeCharacter> &origChars) {
    vector<UnicodeCharacter> ret(origChars.size());
    transform(origChars.begin(),
              origChars.end(),
              ret.begin(),
              [](UnicodeCharacter ch) {
                  auto c = ch.getCodePoint();
                  return ((c >= 0xff01 &&
                           c <= 0xff5e) ?
                          UnicodeCharacter(c - 0xfee0) : ch);
              });
    return ret;
}

string replaceWithNonChar(const string &input, const regex &re) {
    string ret;
    bool isMatch = false;
    static uint32_t nonCharCode = 0;
    
    auto callback = [&](const string &m) {
        if (isMatch) {
            string nonChar = UnicodeCharacter(0xfdd0 + nonCharCode).toString();
            for (size_t i = 0; i < m.size(); ++i) {
                ret += nonChar;
            }
            nonCharCode = (nonCharCode + 1) % 0x20;
        }
        else {
            ret += m;
        }
        isMatch = !isMatch;
    };
    
    sregex_token_iterator begin(input.begin(), input.end(), re, {-1, 0});
    sregex_token_iterator end;
    for_each(begin, end, callback);
    
    return ret;
}

bool isNonCharCode(uint32_t code) {
    return code >= 0xfdd0 && code <= 0xfdef;
}

vector<string> toSegmenterInput(const vector<UnicodeCharacter> &input) {
    static const regex regexUrl(R"([a-z]+://[~.!*'()A-Za-z0-9;/?:@&=+$,%#_-]+)");
    static const regex regexEmail(R"((?:mailto:)?[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:.[a-zA-Z0-9-]+)*)");
    static const regex regexNumber(R"([\d\.,]*[\d\.])");
    static const regex regexLatin(R"([A-Za-z]+)");

    string processed = toString(toHankaku(input));
    processed = replaceWithNonChar(processed, regexUrl);
    processed = replaceWithNonChar(processed, regexEmail);
    processed = replaceWithNonChar(processed, regexNumber);
    processed = replaceWithNonChar(processed, regexLatin);
    auto processedChars = toUnicodeCharacterList(processed);
    assert(input.size() == processedChars.size());

    vector<string> ret;
    uint32_t prevProcessedCharCode = 0;
    
    for (size_t i = 0; i < input.size(); ++i) {
        bool hasSpace;
        string possibleLabelStr("0,1");
        
        auto ch = input[i];
        auto sp = UnicodeCharacter(0);
        if (i < input.size() - 1 &&
            (ch.getCodePoint() == 0x20 || ch.getCodePoint() == 0xa0)){
            sp = ch;
            ++i;
            ch = input[i];
        }
        
        auto processedCharCode = processedChars[i].getCodePoint();
        hasSpace = (i == 0 || sp.getCodePoint() == 0x20);
        
        if (hasSpace) {
            possibleLabelStr = "1";
        }
        else if (isNonCharCode(prevProcessedCharCode) ||
                 isNonCharCode(processedCharCode)) {
            if (prevProcessedCharCode == processedCharCode) {
                possibleLabelStr = "0";
            }
            else if (isNonCharCode(prevProcessedCharCode) &&
                     isNonCharCode(processedCharCode)) {
                possibleLabelStr = "1";
            }
            else {
                possibleLabelStr = "0,1";
            }
        }
        prevProcessedCharCode = processedCharCode;
        ret.emplace_back(string(hasSpace ? " " : "") +
                         ch.toString() +
                         "\t" +
                         possibleLabelStr +
                         "\t" +
                         "*");
    }
    return ret;
}

vector<string> segment(const DataConverter::DataConverterInterface &segmenterConverter,
                       const HighOrderCRF::HighOrderCRFProcessor &segmenterProcessor,
                       const string &line) {
    auto origChars = toUnicodeCharacterList(line);
    origChars.emplace_back(0x3002);  // '。'
    auto segmenterInput = toSegmenterInput(origChars);
    auto dataSequence = segmenterConverter.toDataSequence(segmenterInput);
    auto segmenterOutput = segmenterProcessor.tag(dataSequence.get());
    vector<string> ret;
    string str;
    for (size_t i = 0; i < segmenterOutput.size(); ++i) {
        if ((i > 0 && segmenterOutput[i] == "1") || i == segmenterOutput.size() - 1) {
            ret.emplace_back(str);
            str.clear();
        }
        str.append(origChars[i].toString());
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
    morphemeConcatenator = make_shared<MorphemeConcatenator::MorphemeConcatenatorClass>(concatDicts);
}

vector<vector<string>> JapaneseAnalyzerClass::analyze(const string &line) {
    if (line.empty()) {
        return vector<vector<string>>();
    }
    auto segmented = segment(*segmenterConverter.get(), *segmenterProcessor.get(), line);
    auto tagged = tag(*taggerConverter.get(), *taggerProcessor.get(), segmented);
    auto morphTagged = morphTag(*morphemeDisambiguator.get(), tagged);
    auto concatenated = concatenate(*morphemeConcatenator.get(), morphTagged);
    return concatenated;
}

}  // namespace JapaneseAnalyzer
