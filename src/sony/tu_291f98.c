#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00291F98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00291FA8);

#include "ps2/recovered_types.h"
extern s32 func_0035CA74(s32, s8 *);

s32 func_00291FD0(s32 arg0, s8 *arg1, s32 arg2) {
    return (func_0035CA74(arg0, arg1) != 0) ? 0 : arg2;
}
