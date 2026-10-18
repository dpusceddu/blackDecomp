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

/* Eight bytes at any byte alignment (SN emits ldl/ldr, sdl/sdr for this; see tools/ee_prep.py). */
typedef struct { s64 v; } __attribute__((packed)) M2C_U64;
#define M2C_UNALIGNED64(expr, offset) (((M2C_U64 *)((s8 *)(expr) + (offset)))->v)

#endif
