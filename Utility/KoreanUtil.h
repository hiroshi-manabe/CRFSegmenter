#ifndef HOCRF_UTILITY_KOREAN_UTIL_H_
#define HOCRF_UTILITY_KOREAN_UTIL_H_

#include "CharWithSpace.h"
#include "CharacterCluster.h"

#include <vector>

namespace Utility {

bool isHangeul(UnicodeCharacter ch);
bool isPatchim(UnicodeCharacter ch);
std::vector<UnicodeCharacter> decomposeHangeul(UnicodeCharacter ch);
UnicodeCharacter recomposeHangeul(UnicodeCharacter input, UnicodeCharacter next);

}  // namespace Utility

#endif  // HOCRF_UTILITY_KOREAN_UTIL_H_
