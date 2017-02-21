#include "EncodeUtil.h"

#include <cstddef>
#include <cstring>

namespace Utility {

static uint32_t xorshift32(uint32_t y) {
    y ^= y << 13;
    y ^= y >> 17;
    y ^= y << 15;
    return y;
}

void encodeDecode(uint32_t code, char *buf, size_t size) {
    uint32_t *p = (uint32_t *)buf;
    for (size_t i = 0; i < size / 4; ++i) {
        p[i] ^= code;
        code = xorshift32(code);
    }
    if (size % 4) {
        uint32_t t = 0;
        memcpy(&t, &buf[(size / 4) * 4], size % 4);
        t ^= code;
        memcpy(&buf[(size / 4) * 4], &t, size % 4);
    }
}

void encode(uint32_t code, char *buf, size_t size) {
    encodeDecode(code, buf, size);
}

void decode(char *buf, size_t size) {
    uint32_t code = *(uint32_t *)buf;
    encodeDecode(code, buf, size);
}

}  // namespace Utility
