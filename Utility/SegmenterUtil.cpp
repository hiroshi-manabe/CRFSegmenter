#include "SegmenterUtil.h"

#include "CharWithSpace.h"

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

static vector<UnicodeCharacter> toHankaku(const vector<CharWithSpace> &origChars) {
    vector<UnicodeCharacter> ret(origChars.size());
    transform(origChars.begin(),
              origChars.end(),
              ret.begin(),
              [](CharWithSpace ch) {
                  auto c = ch.getUnicodeCharacter().getCodePoint();
                  return ((c >= 0xff01 &&
                           c <= 0xff5e) ?
                          UnicodeCharacter(c - 0xfee0) : ch.getUnicodeCharacter());
              });
    return ret;
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

vector<string> toSegmenterInput(const vector<CharWithSpace> &input) {
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

    vector<string> ret;
    uint32_t prevProcessedCharCode = 0;
    
    for (size_t i = 0; i < input.size(); ++i) {
        bool hasSpace;
        string possibleLabelStr("0 1");
        
        auto ch = input[i];
        
        auto processedCharCode = processedChars[i].getCodePoint();
        
        if (ch.hasSpace()) {
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
        }
        prevProcessedCharCode = processedCharCode;
        ret.emplace_back(ch.toString() +
                         "\t" +
                         possibleLabelStr +
                         "\t" +
                         "*");
    }
    return ret;
}

}  // namespace Utility
