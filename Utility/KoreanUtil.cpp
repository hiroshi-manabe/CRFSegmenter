#include "KoreanUtil.h"

#include "CharWithSpace.h"
#include "UnicodeCharacter.h"

#include <string>
#include <vector>

using std::vector;

namespace Utility {

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

}  // namespace Utility
