#ifndef HOCRF_UTILITY_STRING_UTIL_H_
#define HOCRF_UTILITY_STRING_UTIL_H_

#include <string>
#include <vector>

namespace Utility {

std::vector<std::string> splitString(const std::string &s, char delim = '\t', int count = 0);
std::vector<std::string> rsplit2(const std::string &s, char delim = '\t');
std::string join(const std::vector<std::string> &v, char delim = '\t');

}  // namespace Utility

#endif  // HOCRF_UTILITY_STRING_UTIL_H_
