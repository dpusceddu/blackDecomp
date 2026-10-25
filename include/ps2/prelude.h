/* Shared declarations for machine-drafted C (tools/autodecomp.py): the integer typedefs and the few m2c macros it emits. */
#ifndef AUTO_PRELUDE_H
#define AUTO_PRELUDE_H

typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long s64;
typedef unsigned long u64;
typedef int s128 __attribute__((mode(TI)));
typedef unsigned int u128 __attribute__((mode(TI)));
typedef float f32;
typedef double f64;

#define NULL ((void *)0)

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* Access at a byte offset of a pointer whose pointee type is unknown. */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Eight bytes at any byte alignment (SN emits ldl/ldr, sdl/sdr for this; see tools/pipeline/ee_prep.py). */
typedef struct { s64 v; } __attribute__((packed)) M2C_U64;
#define M2C_UNALIGNED64(expr, offset) (((M2C_U64 *)((s8 *)(expr) + (offset)))->v)

/* EE instructions m2c cannot read are shown to it as calls of these (tools/pipeline/ee_prep.py); in the source they are inline assembly. */
static inline void __ee_ei(void) { __asm__ volatile("ei"); }
static inline void __ee_di(void) { __asm__ volatile("di"); }
static inline f32 __ee_max_s(f32 a, f32 b) { f32 r; __asm__("max.s %0, %1, %2" : "=f" (r) : "f" (a), "f" (b)); return r; }
static inline f32 __ee_min_s(f32 a, f32 b) { f32 r; __asm__("min.s %0, %1, %2" : "=f" (r) : "f" (a), "f" (b)); return r; }
#include "game/math/scalar.h"
static inline f32 __ee_sqrt_s(f32 value) { return BkSquareRootPS2(value); }
#define EE_COP0(n) \
    static inline s32 __ee_mfc0_##n(void) { s32 r; __asm__ volatile("mfc0 %0, $" #n : "=r" (r)); return r; } \
    static inline void __ee_mtc0_##n(s32 v) { __asm__ volatile("mtc0 %0, $" #n : : "r" (v)); }
EE_COP0(0) EE_COP0(1) EE_COP0(2) EE_COP0(3) EE_COP0(4) EE_COP0(5) EE_COP0(6) EE_COP0(7)
EE_COP0(8) EE_COP0(9) EE_COP0(10) EE_COP0(11) EE_COP0(12) EE_COP0(13) EE_COP0(14) EE_COP0(15)
EE_COP0(16) EE_COP0(17) EE_COP0(18) EE_COP0(19) EE_COP0(20) EE_COP0(21) EE_COP0(22) EE_COP0(23)
EE_COP0(24) EE_COP0(25) EE_COP0(26) EE_COP0(27) EE_COP0(28) EE_COP0(29) EE_COP0(30) EE_COP0(31)

#endif
