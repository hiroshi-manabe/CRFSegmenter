#include <cassert>
#include <cstdint>
#include <string>

#include "UnicodeCharacter.h"
#include "script_data.h"

namespace Utility {

using std::string;

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

UnicodeCharacter UnicodeCharacter::fromString(string::const_iterator it, size_t len, size_t *charCount) {
    assert(len > 0);
    uint32_t codePoint;
    
    if ((it[0] & 0x80) == 0x0) {
        codePoint = it[0];
        *charCount = 1;
    } else if (len >= 2 && (it[0] & 0xe0) == 0xc0 && (it[1] & 0xc0) == 0x80) {
        codePoint = ((it[0] & 0x1f) << 6) | (it[1] & 0x3f);
        *charCount = 2;
        if (codePoint < 0x80) {
            goto ERROR;
        }
    } else if (len >= 3 && (it[0] & 0xf0) == 0xe0 && (it[1] & 0xc0) == 0x80 && (it[2] & 0xc0) == 0x80) {
        codePoint = ((it[0] & 0x0f) << 12) | ((it[1] & 0x3f) << 6) | (it[2] & 0x3f);
        *charCount = 3;
        if (codePoint < 0x800) {
            goto ERROR;
        }
    } else if (len >= 4 && (it[0] & 0xf8) == 0xf0 && (it[1] & 0xc0) == 0x80 && (it[2] & 0xc0) == 0x80 && (it[3] & 0xc0) == 0x80) {
        codePoint = ((it[0] & 0x07) << 18) | ((it[1] & 0x3f) << 12) | ((it[2] & 0x3f) << 6) | (it[3] & 0x3f);
        *charCount = 4;
        if (codePoint < 0x10000) {
            goto ERROR;
        }
    }
    else {
        goto ERROR;
    }

    return UnicodeCharacter(codePoint);

ERROR:
    codePoint = '?';
    *charCount = 1;
    return UnicodeCharacter(codePoint);
}

}  // namespace Utility
