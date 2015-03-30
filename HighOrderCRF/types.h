#ifndef HOCRF_HIGH_ORDER_CRF_TYPES_H_
#define HOCRF_HIGH_ORDER_CRF_TYPES_H_

#include <cstdint>

typedef int32_t label_t;
#define INVALID_LABEL -1

typedef uint16_t pattern_index_t;
typedef uint32_t feature_index_t;

//#define EMULATE_BOS_EOS
#define CRFSUITE_OUTPUT

#endif  // HOCRF_HIGH_ORDER_CRF_TYPES_H_
