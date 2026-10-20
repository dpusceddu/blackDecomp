#ifndef BLACK_MOD_MATH_SCALAR_HPP
#define BLACK_MOD_MATH_SCALAR_HPP
namespace ModMath {
/* EE scalar square root, with the target instruction's exceptional-value behavior.
   Generic FPR constraints; the assembler controls its normal instruction hazards. */
inline float SquareRoot(float value) {
 float root;
 asm("sqrt.s outf, inf" : "=f outf"(root) : "f inf"(value));
 return root;
}
}
#endif
