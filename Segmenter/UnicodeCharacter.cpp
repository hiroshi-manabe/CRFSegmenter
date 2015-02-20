#include "UnicodeCharacter.h"
#include "script_data.h"

#include <cassert>
#include <cstdint>
#include <string>

namespace Segmenter {

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

UnicodeCharacter UnicodeCharacter::fromString(const char *buf, size_t len, size_t *charCount) {
    assert(len > 0);
    uint32_t codePoint;
    
    if ((buf[0] & 0x80) == 0x0) {
        codePoint = buf[0];
        *charCount = 1;
    } else if (len >= 2 && (buf[0] & 0xe0) == 0xc0 && (buf[1] & 0xc0) == 0x80) {
        codePoint = ((buf[0] & 0x1f) << 6) | (buf[1] & 0x3f);
        *charCount = 2;
        if (codePoint < 0x80) {
            goto ERROR;
        }
    } else if (len >= 3 && (buf[0] & 0xf0) == 0xe0 && (buf[1] & 0xc0) == 0x80 && (buf[2] & 0xc0) == 0x80) {
        codePoint = ((buf[0] & 0x0f) << 12) | ((buf[1] & 0x3f) << 6) | (buf[2] & 0x3f);
        *charCount = 3;
        if (codePoint < 0x800) {
            goto ERROR;
        }
    } else if (len >= 4 && (buf[0] & 0xf8) == 0xf0 && (buf[1] & 0xc0) == 0x80 && (buf[2] & 0xc0) == 0x80 && (buf[3] & 0xc0) == 0x80) {
        codePoint = ((buf[0] & 0x07) << 18) | ((buf[1] & 0x3f) << 12) | ((buf[2] & 0x3f) << 6) | (buf[3] & 0x3f);
        *charCount = 4;
        if (codePoint < 0x10000) {
            goto ERROR;
        }
    }
    return UnicodeCharacter(codePoint);

ERROR:
    codePoint = '?';
    *charCount = 1;
    return UnicodeCharacter(codePoint);
}

}
