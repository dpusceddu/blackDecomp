#pragma once
#include <cstdint>

namespace ee::fpu {
struct Arithmetic {
    uint32_t bits = 0;
    bool overflow = false, underflow = false, divide_zero = false, invalid = false;
    bool product_underflow = false;
    bool operator==(const Arithmetic&) const = default;
};
// Bit-level EE number operations: exponent 255 is finite; exponent zero is
// signed zero for comparisons/conversion. No host floating-point is used.
uint32_t flush_zero(uint32_t value);
bool equal(uint32_t a, uint32_t b);
bool less(uint32_t a, uint32_t b);
uint32_t maximum(uint32_t a, uint32_t b);
uint32_t minimum(uint32_t a, uint32_t b);
uint32_t from_integer(uint32_t value);
uint32_t to_integer(uint32_t value);
Arithmetic add(uint32_t a, uint32_t b);
Arithmetic subtract(uint32_t a, uint32_t b);
Arithmetic multiply(uint32_t a, uint32_t b);
Arithmetic divide(uint32_t a, uint32_t b);
Arithmetic square_root(uint32_t value);
Arithmetic reciprocal_root(uint32_t numerator, uint32_t radicand);
Arithmetic accumulate(uint32_t accumulator, uint32_t a, uint32_t b,
                      bool accumulator_overflow, bool subtract_product);
Arithmetic accumulate_product(uint32_t accumulator, Arithmetic product,
                              bool accumulator_overflow, bool subtract_product);
} // namespace ee::fpu
