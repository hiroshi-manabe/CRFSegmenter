#ifndef HOCRF_UTILITY_KOREAN_UTIL_H_
#define HOCRF_UTILITY_KOREAN_UTIL_H_

#include "CharWithSpace.h"
#include "UnicodeCharacter.h"

#include <vector>

namespace Utility {

bool isHangeul(UnicodeCharacter ch);
bool isPatchim(UnicodeCharacter ch);
std::vector<CharWithSpace> decomposeHangeul(CharWithSpace ch);
CharWithSpace recomposeHangeul(CharWithSpace input, CharWithSpace next);

}  // namespace Utility

#endif  // HOCRF_UTILITY_KOREAN_UTIL_H_
