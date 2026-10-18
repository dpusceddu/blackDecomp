#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * func_0031E9D8(void *, s32 *, void *, s32, void *);

s32 func_00321EE0(void *arg0, s32 *arg1, s32 arg2, void *arg3, s32 arg4, s32 arg5) {
    u8 sp[8] __attribute__((aligned(16)));
    func_0031E9D8(arg0, arg1, arg3, arg2, sp);
    return *(s32 *)(sp + 0);
}
