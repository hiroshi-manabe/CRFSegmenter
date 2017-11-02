#include <cassert>
#include <cstdint>
#include <string>
#include <vector>

#include "UnicodeCharacter.h"
#include "script_data.h"

namespace Utility {

using std::string;
using std::vector;

UnicodeCharacter::UnicodeCharacter() {
    this->codePoint = 0;
}

UnicodeCharacter::~UnicodeCharacter() {
}

UnicodeCharacter::UnicodeCharacter(const UnicodeCharacter &uchar) {
    uchar.getCodePoint();
    codePoint = uchar.getCodePoint();
}

UnicodeCharacter::UnicodeCharacter(uint32_t codePoint) {
    assert(codePoint < 0x110000);
    this->codePoint = codePoint;
}

UnicodeCharacter::UnicodeCharacter(string::const_iterator beginIterator, string::const_iterator endIterator, size_t *charCount) {
    assert(endIterator > beginIterator);
    uint32_t codePoint;
    
    if ((beginIterator[0] & 0x80) == 0x0) {
        codePoint = beginIterator[0];
        *charCount = 1;
    } else if (endIterator > beginIterator + 1 && (beginIterator[0] & 0xe0) == 0xc0 && (beginIterator[1] & 0xc0) == 0x80) {
        codePoint = ((beginIterator[0] & 0x1f) << 6) | (beginIterator[1] & 0x3f);
        *charCount = 2;
        if (codePoint < 0x80) {
            goto ERROR;
        }
    } else if (endIterator > beginIterator + 2 && (beginIterator[0] & 0xf0) == 0xe0 && (beginIterator[1] & 0xc0) == 0x80 && (beginIterator[2] & 0xc0) == 0x80) {
        codePoint = ((beginIterator[0] & 0x0f) << 12) | ((beginIterator[1] & 0x3f) << 6) | (beginIterator[2] & 0x3f);
        *charCount = 3;
        if (codePoint < 0x800) {
            goto ERROR;
        }
    } else if (endIterator > beginIterator + 3 && (beginIterator[0] & 0xf8) == 0xf0 && (beginIterator[1] & 0xc0) == 0x80 && (beginIterator[2] & 0xc0) == 0x80 && (beginIterator[3] & 0xc0) == 0x80) {
        codePoint = ((beginIterator[0] & 0x07) << 18) | ((beginIterator[1] & 0x3f) << 12) | ((beginIterator[2] & 0x3f) << 6) | (beginIterator[3] & 0x3f);
        *charCount = 4;
        if (codePoint < 0x10000) {
            goto ERROR;
        }
    }
    else {
        goto ERROR;
    }

    this->codePoint = codePoint;
    return;

ERROR:
    this->codePoint = '?';
    *charCount = 1;
}

string UnicodeCharacter::toString() const {
    string ret;
    if (codePoint < 0x80) {
        ret += (char)(codePoint & 0x7f);
    } else if (codePoint < 0x800) {
        ret += (char)((codePoint >> 6) | 0xc0);
        ret += (char)((codePoint & 0x3f) | 0x80);
    } else if (codePoint < 0x10000) {
        ret += (char)((codePoint >> 12) | 0xe0);
        ret += (char)(((codePoint >> 6) & 0x3f) | 0x80);
        ret += (char)((codePoint & 0x3f) | 0x80);
    } else if (codePoint < 0x110000) {
        ret += (char)((codePoint >> 18) | 0xf0);
        ret += (char)(((codePoint >> 12) & 0x3f) | 0x80);
        ret += (char)(((codePoint >> 6) & 0x3f) | 0x80);
        ret += (char)((codePoint & 0x3f) | 0x80);
    } else {
        ret += '?';
    }
    return ret;
}

string UnicodeCharacter::getCharacterType() const {
    return ScriptData::codePointToScriptString(codePoint);
}

uint32_t UnicodeCharacter::getCodePoint() const {
    return codePoint;
}

vector<UnicodeCharacter> UnicodeCharacter::stringToUnicodeCharacterList(const string &orig) {
    vector<UnicodeCharacter> ret;
    for (auto it = orig.begin(); it != orig.end(); ) {
        size_t charCount;
        ret.emplace_back(it, orig.end(), &charCount);
        it += charCount;
    }
    return ret;
}

string UnicodeCharacter::unicodeCharacterListToString(const vector<UnicodeCharacter> &origChars) {
    string ret;
    for (const auto c : origChars) {
        ret += c.toString();
    }
    return ret;
}

}  // namespace Utility
