#ifndef HOCRF_UTILITY_ENCRYPTION_UTIL_H_
#define HOCRF_UTILITY_ENCRYPTION_UTIL_H_

#include <cstddef>
#include <cstdint>

namespace Utility {

void encrypt(char *buf, size_t size);
void decrypt(char *buf, size_t size);

}  // namespace Utility

#endif  // HOCRF_UTILITY_ENCRYPTION_UTIL_H_
