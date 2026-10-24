#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00291000(void *, s32, s32);

s32 func_00291C38(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 sp[24] __attribute__((aligned(16)));

    *(s32 *)(sp + 0) = arg0;
    *(s32 *)(sp + 4) = arg1;
    *(s32 *)(sp + 8) = arg2;
    *(s64 *)(sp + 16) = (s64) arg3;
    return func_00291000(sp, arg1, arg2);
}
