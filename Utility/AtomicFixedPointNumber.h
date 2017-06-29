#ifndef HOCRF_UTILITY_FIXED_POINT_NUMBER_H_
#define HOCRF_UTILITY_FIXED_POINT_NUMBER_H_

#include <atomic>
#include <cstdint>

namespace Utility {

class AtomicFixedPointNumber64 {
 public:
    static const int_least64_t SCALING_CONSTANT = 0x100000000L;
    AtomicFixedPointNumber64(double d = 0.0) {
        *this = d;
    }
   
    AtomicFixedPointNumber64 &operator=(double d) {
        num_ = d * SCALING_CONSTANT;
    }

    operator double() const {
        return (double)num_ / SCALING_CONSTANT;
    }

    AtomicFixedPointNumber64 &operator+=(double d) {
        num_ += d * SCALING_CONSTANT;
    }

 private:
    std::atomic_int_least64_t num_;
};

}  // namespace Utility

#endif  // HOCRF_UTILITY_FIXED_POINT_NUMBER_H_

