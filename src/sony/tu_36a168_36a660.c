#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * func_0036A528(u32, s32, void *, s32, void *, u32, s32);

s32 * func_0036A660(s32 arg0, void *arg1, s32 arg2, void *arg3, s32 arg4, s32 arg5) {
    return func_0036A528((u32) arg0, 0, arg1, arg2, arg3, (u32) arg4, arg5);
}

s32 * func_0036A6A0(s32 arg0, void *arg1, s32 arg2, void *arg3, s32 arg4, s32 arg5) {
    return func_0036A528((u32) arg0, 1, arg1, arg2, arg3, (u32) arg4, arg5);
}
