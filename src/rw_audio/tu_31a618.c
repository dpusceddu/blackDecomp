#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

s32 func_0031A618(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) (((u8) M2C_FIELD(arg0, u8 *, 0x8A) >> 2) & 1);
    return arg0;
}
