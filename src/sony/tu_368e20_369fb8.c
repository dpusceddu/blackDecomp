#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * func_003691A8(s32, void *, s32, s8 *, void *);
extern s32 func_00369EC0(void *, void *, s32);

s32 * func_00369FB8(void *arg0, s32 arg1, s8 *arg2, void *arg3) {
    u8 sp[8] __attribute__((aligned(16)));

    *(void * *)(sp + 0) = arg0;
    return func_003691A8((s32) func_00369EC0, sp, arg1, arg2, arg3);
}
