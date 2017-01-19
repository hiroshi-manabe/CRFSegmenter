#ifndef HOCRF_UTILITY_SPLIT_STRING_H_
#define HOCRF_UTILITY_SPLIT_STRING_H_

#include <string>
#include <vector>

namespace Utility {

std::vector<std::string> splitString(const std::string &s, char delim = '\t', int count = 0);
std::string join(const std::vector<std::string> &v, char delim = '\t');

}  // namespace Utility

#endif  // HOCRF_UTILITY_SPLIT_STRING_H_
