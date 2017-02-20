#ifndef HOCRF_UTILITY_ENCODE_UTIL_H_
#define HOCRF_UTILITY_ENCODE_UTIL_H_

#include <cstddef>
#include <cstdint>

namespace Utility {

void encode(uint32_t code, char *buf, size_t size);
void decode(char *buf, size_t size);

}  // namespace Utility

#endif  // HOCRF_UTILITY_ENCODE_UTIL_H_
