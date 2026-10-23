#include "fpu.hpp"
#include <algorithm>
#include <array>
#include <bit>

namespace ee::fpu {
uint32_t flush_zero(uint32_t value) {
    return value & 0x7f800000 ? value : value & 0x80000000;
}
static uint32_t order(uint32_t value) {
    return value & 0x80000000 ? ~value : value ^ 0x80000000;
}
bool equal(uint32_t a, uint32_t b) {
    a = flush_zero(a); b = flush_zero(b);
    return a == b || (!(a & 0x7fffffff) && !(b & 0x7fffffff));
}
bool less(uint32_t a, uint32_t b) {
    return !equal(a,b) && order(flush_zero(a)) < order(flush_zero(b));
}
uint32_t maximum(uint32_t a, uint32_t b) { return order(a) >= order(b) ? a : b; }
uint32_t minimum(uint32_t a, uint32_t b) { return order(a) <= order(b) ? a : b; }
uint32_t from_integer(uint32_t value) {
    const uint32_t sign = value & 0x80000000;
    uint32_t magnitude = sign ? 0u-value : value;
    if (!magnitude) return 0;
    const unsigned exponent = 31-std::countl_zero(magnitude);
    const uint32_t significand = exponent > 23 ? magnitude >> (exponent-23) : magnitude << (23-exponent);
    return sign | ((exponent+127) << 23) | (significand & 0x7fffff);
}
uint32_t to_integer(uint32_t value) {
    const bool sign = value & 0x80000000;
    const int exponent = int(value >> 23 & 255)-127;
    if (exponent < 0) return 0;
    if (exponent > 30) return sign ? 0x80000000 : 0x7fffffff;
    const uint32_t significand = (value & 0x7fffff) | 0x800000;
    const uint32_t magnitude = exponent > 23 ? significand << (exponent-23) : significand >> (23-exponent);
    return sign ? 0u-magnitude : magnitude;
}

namespace {
constexpr uint32_t sign_bit = 0x80000000;
unsigned exponent(uint32_t value) { return value >> 23 & 255; }
uint32_t significand(uint32_t value) { return (value & 0x7fffff) | 0x800000; }
Arithmetic pack(uint32_t sign, int exp, uint64_t magnitude) {
    if (exp > 255) return {sign | 0x7fffffff, true};
    if (exp <= 0) return {sign, false, magnitude != 0};
    return {sign | uint32_t(exp) << 23 | (uint32_t(magnitude) & 0x7fffff)};
}

// A bit-serial model of the multiplier's relevant columns. The ordinary
// 48-bit product is corrected by the carry discarded at column 15. Inputs and
// the fixed cell connections describe the hardware; no emulator code is used.
using Row = std::array<bool, 16>;
struct Rows { Row sum{}, carry{}; };
Rows compress(const Row& a, const Row& b, const Row& c) {
    Rows out;
    for (unsigned column = 0; column < a.size(); ++column) {
        const unsigned ones = unsigned(a[column])+unsigned(b[column])+unsigned(c[column]);
        out.sum[column] = ones & 1;
        if (column+1 < a.size()) out.carry[column+1] = ones >= 2;
    }
    return out;
}
uint64_t multiply_significands(uint32_t a, uint32_t b) {
    std::array<Row, 8> partial{};
    std::array<bool, 8> negative{};
    // Radix-4 digits: d[k] = b[2k-1] + b[2k] - 2*b[2k+1].
    for (unsigned row = 0; row < partial.size(); ++row) {
        const auto digit_bit = [&](int column) { return column < 0 ? 0 : int(b >> column & 1); };
        const int digit = digit_bit(int(row)*2-1)+digit_bit(row*2)-2*digit_bit(row*2+1);
        negative[row] = digit < 0;
        const uint32_t magnitude = a * unsigned(digit < 0 ? -digit : digit);
        for (unsigned column = row*2; column < 16; ++column)
            partial[row][column] = bool(magnitude >> (column-row*2) & 1) != negative[row];
    }
    const Row group_a_sum = partial[1];
    auto group_a = compress(group_a_sum, partial[2], partial[3]);
    const bool omitted_10 = partial[5][10], omitted_11 = partial[5][11];
    for (unsigned column = 0; column < 11; ++column) partial[4][column] = false;
    for (unsigned column = 0; column < 12; ++column) partial[5][column] = false;
    auto group_b = compress(partial[4], partial[5], partial[6]);
    group_b.carry[12] = group_b.carry[12] || negative[6];
    group_b.carry[11] = group_b.carry[11] || omitted_11;
    // Two connections from row 5 are folded into the last partial product.
    partial[7][10] = partial[7][10] || (omitted_10 != negative[5]);
    partial[7][11] = partial[7][11] || (omitted_10 && negative[5]);
    auto first = compress(partial[0], group_a.sum, group_a.carry);
    auto second = compress(partial[7], group_b.sum, group_b.carry);
    auto third = compress(first.carry, second.sum, second.carry);
    auto fourth = compress(first.sum, third.sum, third.carry);
    // Add the last Booth correction before dropping columns 0..14.
    if (negative[7]) {
        for (unsigned column = 14; column < 16; ++column) {
            fourth.carry[column] = !fourth.carry[column];
            if (fourth.carry[column]) break;
        }
    }
    const bool column_15 = fourth.sum[15] != fourth.carry[15];
    const uint64_t product = uint64_t(a)*b;
    return product - (column_15 != bool(product & 0x8000) ? 0x8000 : 0);
}

// Redundant remainder for radix-2 SRT. The two rows deliberately remain
// separate: collapsing them to an integer changes the next-digit estimate.
struct Remainder {
    uint32_t parity = 0, carries = 0;
    int digit() const {
        const uint32_t high = (parity & 0xff000000)+carries;
        const int32_t estimate = std::bit_cast<int32_t>(high | (parity & 0x00ffffff));
        if (estimate >= 0x00800000) return 1;
        if (estimate < -0x01000000) return -1;
        return 0;
    }
    Remainder subtract_digit(uint32_t divisor, int selected) const {
        const std::array<uint32_t,3> input = {
            parity, carries+unsigned(selected > 0),
            selected > 0 ? ~divisor : selected < 0 ? divisor : 0
        };
        Remainder next;
        for (unsigned column = 0; column < 32; ++column) {
            unsigned population = 0;
            for (const auto row : input) population += row >> column & 1;
            if (population & 1) next.parity |= uint32_t(1) << column;
            if (population >= 2 && column < 31) next.carries |= uint32_t(1) << (column+1);
        }
        return next;
    }
    void scale() { parity *= 2; carries *= 2; }
};
} // namespace

Arithmetic add(uint32_t a, uint32_t b) {
    a = flush_zero(a); b = flush_zero(b);
    if ((a & 0x7fffffff) < (b & 0x7fffffff)) std::swap(a,b);
    const uint32_t sign = a & sign_bit;
    const int ea = int(exponent(a)), eb = int(exponent(b));
    if (!eb) return {ea ? a : a & b & sign_bit};
    const unsigned distance = unsigned(ea-eb);
    if (distance > 24) return {a};
    const uint32_t lhs = significand(a)*2, rhs = significand(b)*2 >> distance;
    const uint32_t magnitude = ((a^b) & sign_bit) ? lhs-rhs : lhs+rhs;
    if (!magnitude) return {};
    const unsigned top = 31-std::countl_zero(magnitude);
    const uint32_t normalized = top >= 23 ? magnitude >> (top-23) : magnitude << (23-top);
    return pack(sign,ea+int(top)-24,normalized);
}
Arithmetic subtract(uint32_t a, uint32_t b) { return add(a,b ^ sign_bit); }
Arithmetic multiply(uint32_t a, uint32_t b) {
    const uint32_t sign = (a^b) & sign_bit;
    const int ea = int(exponent(a)), eb = int(exponent(b));
    if (!ea || !eb) return {sign};
    const uint64_t product = multiply_significands(significand(a),significand(b));
    const unsigned carry = bool(product & (uint64_t(1) << 47));
    return pack(sign,ea+eb-127+int(carry),product >> (23+carry));
}

Arithmetic divide(uint32_t a, uint32_t b) {
    const uint32_t sign = (a^b) & sign_bit;
    const int ea = int(exponent(a)), eb = int(exponent(b));
    if (!eb) return {sign | 0x7fffffff, false, false, bool(ea), !ea};
    if (!ea) return {sign};
    Remainder remainder{significand(a)*4,0};
    uint32_t quotient = 0;
    int selected = 1;
    for (unsigned cycle = 0; cycle < 25; ++cycle) {
        quotient = quotient*2+uint32_t(selected);
        auto next = remainder.subtract_digit(significand(b)*4,selected);
        selected = selected ? next.digit() : remainder.digit();
        remainder = next;
        remainder.scale();
    }
    const unsigned normal = quotient >= 0x1000000;
    return pack(sign,ea-eb+126+int(normal),quotient >> normal);
}

Arithmetic square_root(uint32_t value) {
    // The numerical result is nonnegative even for -0 in the hardware logs.
    // Invalid follows the sign input to the divider, including negative zero.
    const bool negative = value & sign_bit;
    const int exp = int(exponent(value));
    if (!exp) return {0,false,false,false,negative};
    Remainder remainder{significand(value)*unsigned(exp & 1 ? 2 : 4),0};
    uint32_t root = 0;
    int selected = 1;
    for (unsigned cycle = 0; cycle < 25; ++cycle) {
        const unsigned position = 24-cycle;
        const uint32_t delta = uint32_t(selected) << position;
        // (r+d)^2-r^2 = d(2r+d). This is the square-root digit recurrence.
        const uint32_t trial = root+delta;
        root += delta*2;
        auto next = remainder.subtract_digit(trial,selected);
        selected = selected ? next.digit() : remainder.digit();
        remainder = next;
        remainder.scale();
    }
    auto result = pack(0,(exp+127)/2,root >> 2);
    result.invalid = negative;
    return result;
}

Arithmetic reciprocal_root(uint32_t numerator, uint32_t radicand) {
    const auto root = square_root(radicand & 0x7fffffff);
    auto result = divide(numerator,root.bits);
    result.invalid = result.invalid || bool(radicand & sign_bit);
    return result;
}

Arithmetic accumulate(uint32_t accumulator, uint32_t a, uint32_t b,
                      bool accumulator_overflow, bool subtract_product) {
    return accumulate_product(accumulator,multiply(a,b),accumulator_overflow,subtract_product);
}
Arithmetic accumulate_product(uint32_t accumulator, Arithmetic product,
                              bool accumulator_overflow, bool subtract_product) {
    if (product.overflow) {
        if (subtract_product) product.bits ^= sign_bit;
        return product;
    }
    if (accumulator_overflow) {
        Arithmetic result{accumulator,true};
        result.product_underflow = product.underflow;
        return result;
    }
    auto result = subtract_product ? subtract(accumulator,product.bits) : add(accumulator,product.bits);
    result.product_underflow = product.underflow;
    return result;
}
} // namespace ee::fpu
