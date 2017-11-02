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

vector<UnicodeCharacter> decomposeHangeul(UnicodeCharacter ch) {
    vector<UnicodeCharacter> ret{ ch };
    if (!isHangeul(ch)) {
        return ret;
    }
    uint32_t code = ch.getCodePoint();
    uint32_t patchimCode = (code - 0xac00) % 28;
    if (patchimCode == 4 ||
        patchimCode == 8 ||
        patchimCode == 16 ||
        patchimCode == 17 ||
        patchimCode == 20) {
        ret = { { code - patchimCode }, { 0xe000 + patchimCode } };
    }
    else if (patchimCode == 10) {
        ret = { { code - 2 }, { 0xe000 + 16 } };
    }
    return ret;
}

UnicodeCharacter recomposeHangeul(UnicodeCharacter input, UnicodeCharacter next) {
    UnicodeCharacter ret(input);
    if (!isHangeul(input) || !isPatchim(next)) {
        return ret;
    }
    uint32_t code = input.getCodePoint();
    uint32_t patchimCode = (code - 0xac00) % 28;
    uint32_t newPatchimCode = next.getCodePoint() - 0xe000;
    if (patchimCode == 0) {
        return { code + newPatchimCode };
    }
    else if (patchimCode == 8 && newPatchimCode == 16) {
        return { code + 2 };
    }
    return ret;
}

}  // namespace Utility
