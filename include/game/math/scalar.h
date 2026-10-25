#ifndef BLACK_MOD_MATH_SCALAR_H
#define BLACK_MOD_MATH_SCALAR_H
/* EE hardware square root; generic FPR operands and target exception behavior. */
static inline float BkSquareRootPS2(float value) {
 float root;
 __asm__("sqrt.s %0, %1" : "=f"(root) : "f"(value));
 return root;
}
#endif
