#ifndef BLACK_MOD_MATH_SCALAR_HPP
#define BLACK_MOD_MATH_SCALAR_HPP
#include "game/math/scalar.h"
namespace Math {
/* EE scalar square root, with the target instruction's exceptional-value behavior.
   Generic FPR constraints; the assembler controls its normal instruction hazards. */
inline float SquareRoot(float value) {
 return BkSquareRootPS2(value);
}
}
#endif
