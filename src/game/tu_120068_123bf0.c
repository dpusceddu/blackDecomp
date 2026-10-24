#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 * func_00123C90(s32 *, void *, void *);

s32 func_00123BF0(s32 *arg0, void *arg1, s32 arg2, s32 arg3) {
    return *func_00123C90(arg0, (void *)7, arg1) >= 2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00123C20);
