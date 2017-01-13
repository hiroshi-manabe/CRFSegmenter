#ifndef HOCRF_HIGH_ORDER_CRF_UTILITY_H_
#define HOCRF_HIGH_ORDER_CRF_UTILITY_H_

#include <string>
#include <vector>

namespace HighOrderCRF {

std::vector<std::string> splitString(const std::string &s, char delim = '\t', int count = 0);

}  // namespace std

#endif  // HOCRF_HIGH_ORDER_CRF_UTILITY_H_
