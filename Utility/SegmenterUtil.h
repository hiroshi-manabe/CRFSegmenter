#ifndef HOCRF_UTILITY_SEGMENTER_UTIL_H_
#define HOCRF_UTILITY_SEGMENTER_UTIL_H_

#include "CharWithSpace.h"

#include <string>
#include <vector>

namespace Utility {

std::vector<std::string> toSegmenterInput(const std::vector<CharWithSpace> &input);

}  // namespace Utility

#endif  // HOCRF_UTILITY_SEGMENTER_UTIL_H_