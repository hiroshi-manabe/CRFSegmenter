#include "SegmenterUtil.h"

#include "CharacterCluster.h"
#include "CharWithSpace.h"
#include "UnicodeCharacter.h"

#include <algorithm>
#include <cassert>
#include <regex>
#include <string>
#include <vector>

using std::for_each;
using std::regex;
using std::sregex_token_iterator;
using std::string;
using std::transform;
using std::vector;

namespace Utility {

static vector<UnicodeCharacter> hanZenConverter(const vector<UnicodeCharacter> &origChars, bool toZenkaku) {
    vector<UnicodeCharacter> ret(origChars.size());
    transform(origChars.begin(),
              origChars.end(),
              ret.begin(),
              [&](UnicodeCharacter ch) {
                  auto c = ch.getCodePoint();
                  return (toZenkaku ?
                      (c == 0x20 ? 0x3000 : c == 0x22 ? 0x201c : ((c >= 0x21 && c <= 0x7e) ? c + 0xfee0 : ch)) :
                      (c == 0x3000 ? 0x20 : ((c >= 0xff01 && c <= 0xff5e) ? c - 0xfee0 : ch)));
              });
    return ret;
}

static vector<UnicodeCharacter> toHankaku(const vector<UnicodeCharacter> &origChars) {
    return hanZenConverter(origChars, false);
}

static vector<UnicodeCharacter> toZenkaku(const vector<UnicodeCharacter> &origChars) {
    return hanZenConverter(origChars, true);
}

static string replaceWithNonChar(const string &input, const regex &re) {
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

static bool isNonCharCode(uint32_t code) {
    return code >= 0xfdd0 && code <= 0xfdef;
}

vector<string> toSegmenterInput(const vector<UnicodeCharacter> &input, bool convertToZenkaku) {
    static const regex regexUrl(R"([a-z]+://[~.!*'()A-Za-z0-9;/?:@&=+$,%#_-]+)");
    static const regex regexEmail(R"((?:mailto:)?[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:.[a-zA-Z0-9-]+)*)");
    static const regex regexNumber(R"([\d\.,]*[\d\.])");
    static const regex regexLatin(R"([A-Za-z]+)");

    string processed = UnicodeCharacter::unicodeCharacterListToString(toHankaku(input));
    processed = replaceWithNonChar(processed, regexUrl);
    processed = replaceWithNonChar(processed, regexEmail);
    processed = replaceWithNonChar(processed, regexNumber);
    processed = replaceWithNonChar(processed, regexLatin);
    auto processedChars = UnicodeCharacter::stringToUnicodeCharacterList(processed);
    assert(input.size() == processedChars.size());
    auto inputZen = convertToZenkaku ? toZenkaku(input) : input;

    vector<string> ret;
    uint32_t prevProcessedCharCode = 0;
    bool hasSpace;
    
    for (size_t i = 0; i < inputZen.size(); ++i) {
        string possibleLabelStr("0 1");
        
        auto ch = inputZen[i];
        auto processedCharCode = processedChars[i].getCodePoint();
        
        hasSpace = (i == 0 || ch.getCodePoint() == ' ' && i < inputZen.size() - 1);
        if (hasSpace) {
            possibleLabelStr = "1";
            if (i != 0) {
                ++i;
            }
            ch = inputZen[i];
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

}  // namespace Utility
