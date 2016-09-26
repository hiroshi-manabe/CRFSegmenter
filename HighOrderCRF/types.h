#ifndef HOCRF_HIGH_ORDER_CRF_TYPES_H_
#define HOCRF_HIGH_ORDER_CRF_TYPES_H_

#include <cstdint>
#include <cmath>

typedef int32_t label_t;
#define INVALID_LABEL -1

typedef uint16_t pattern_index_t;
typedef uint32_t feature_index_t;
#define INVALID_FEATURE ((uint32_t)-1);

typedef uint32_t weight_t;

inline double weight_to_double(weight_t w) {
    return *(reinterpret_cast<float *>(&w));
}

inline weight_t double_to_weight(double d) {
    float f = static_cast<float>(d);
    return *(reinterpret_cast<weight_t*>(&f));
}

#endif  // HOCRF_HIGH_ORDER_CRF_TYPES_H_
