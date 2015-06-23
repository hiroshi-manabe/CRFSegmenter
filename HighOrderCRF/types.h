#ifndef HOCRF_HIGH_ORDER_CRF_TYPES_H_
#define HOCRF_HIGH_ORDER_CRF_TYPES_H_

#include <cstdint>
#include <cmath>

typedef int32_t label_t;
typedef uint32_t label_t_unsigned;
#define INVALID_LABEL -1

typedef uint16_t pattern_index_t;
typedef uint32_t feature_index_t;
#define INVALID_FEATURE ((uint32_t)-1);

typedef uint16_t weight_t;

#define DBL_SGN_DIGIT 63
#define HLF_SGN_DIGIT 15
#define DBL_EXP_DIGIT 52
#define HLF_EXP_DIGIT 10

#define HLF_SGN_MASK (1LLU << HLF_SGN_DIGIT)
#define HLF_EXP_MASK (((1LLU << (HLF_SGN_DIGIT - HLF_EXP_DIGIT)) - 1) << HLF_EXP_DIGIT)
#define HLF_SIG_MASK ((1LLU << HLF_EXP_DIGIT) - 1)
#define HLF_EXP_OFFSET 15
#define HLF_EXP_MAX 15
#define HLF_EXP_MIN -14

#define DBL_SGN_MASK (1LLU << DBL_SGN_DIGIT)
#define DBL_EXP_MASK (((1LLU << (DBL_SGN_DIGIT - DBL_EXP_DIGIT)) - 1) << DBL_EXP_DIGIT)
#define DBL_SIG_MASK ((1LLU << DBL_EXP_DIGIT) - 1)
#define DBL_EXP_OFFSET 1023

// assuming double is in IEEE 754 format.
inline double weight_to_double(weight_t w) {
    if (w == 0) {
        return 0;
    }
    uint64_t u64 = w;
    uint64_t ret = ((u64 & HLF_SGN_MASK) << (DBL_SGN_DIGIT - HLF_SGN_DIGIT)) |
        (((u64 & HLF_EXP_MASK) + ((DBL_EXP_OFFSET - HLF_EXP_OFFSET) << HLF_EXP_DIGIT)) << (DBL_EXP_DIGIT - HLF_EXP_DIGIT)) |
        ((u64 & HLF_SIG_MASK) << (DBL_EXP_DIGIT - HLF_EXP_DIGIT));
    return *((double*)&ret);
}

// assuming double is in IEEE 754 format.
inline weight_t double_to_weight(double d) {
    if (d == 0) {
        return 0;
    }
    uint64_t *p = (uint64_t*)&d;
    int exp = ((*p & DBL_EXP_MASK) >> DBL_EXP_DIGIT) + (HLF_EXP_OFFSET - DBL_EXP_OFFSET);
    if (exp > HLF_EXP_MAX + HLF_EXP_OFFSET) {
        exp = HLF_EXP_MAX + HLF_EXP_OFFSET;
    }
    else if (exp < HLF_EXP_MIN + HLF_EXP_OFFSET) {
        return 0;
    }
    return (weight_t)(((*p >> (DBL_SGN_DIGIT - HLF_SGN_DIGIT)) & HLF_SGN_MASK) | (exp << HLF_EXP_DIGIT) | ((*p >> (DBL_EXP_DIGIT - HLF_EXP_DIGIT)) & HLF_SIG_MASK));
}

#endif  // HOCRF_HIGH_ORDER_CRF_TYPES_H_
