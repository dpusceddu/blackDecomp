#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_0029AEF0(s32 *, s32 *);

void func_0029B050(s32 *arg0, s32 arg1) {
    func_0029AEF0(arg0, (s32 *)0x20);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029B058);
