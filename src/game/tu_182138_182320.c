#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00182608(void *, s128, s32, f32);
extern f32 func_0018DA40(void *);

s32 func_00182320(void *arg0, s128 arg1, s32 arg2) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x310), s8 *, 0x6D4) = 0;
    return func_00182608(arg0, arg1, arg2, func_0018DA40(M2C_FIELD(arg0, void **, 0x310) + 0xC94));
}
