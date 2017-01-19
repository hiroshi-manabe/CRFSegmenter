#ifndef HOCRF_UTILITY_FILE_UTIL_H_
#define HOCRF_UTILITY_FILE_UTIL_H_

#include <istream>
#include <string>
#include <vector>

namespace Utility {

std::vector<std::string> readSequence(std::istream &is);

}  // namespace Utility

#endif  // HOCRF_UTILITY_FILE_UTIL_H_
