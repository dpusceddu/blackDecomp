#ifndef BLACK_PS2_EE_TYPES_H
#define BLACK_PS2_EE_TYPES_H
/* SN EE GCC 2.95 target-recipe widths, not host widths. Sony recipes are not assumed. */
typedef signed char EeS8;
typedef unsigned char EeU8;
typedef signed short EeS16;
typedef unsigned short EeU16;
typedef signed int EeS32;
typedef unsigned int EeU32;
typedef signed long EeS64;
typedef unsigned long EeU64;
typedef int EeS128 __attribute__((mode(TI)));
typedef unsigned int EeU128 __attribute__((mode(TI)));
typedef char EeByteIs8[sizeof(EeS8) == 1 ? 1 : -1];
typedef char EeShortIs16[sizeof(EeS16) == 2 ? 1 : -1];
typedef char EeIntIs32[sizeof(EeS32) == 4 ? 1 : -1];
typedef char EePointerIs32[sizeof(void *) == 4 ? 1 : -1];
typedef char EeLongIs64[sizeof(long) == 8 ? 1 : -1];
typedef char EeLongLongIs128[sizeof(long long) == 16 ? 1 : -1];
typedef char EeQuadIs128[sizeof(EeS128) == 16 ? 1 : -1];
#endif
