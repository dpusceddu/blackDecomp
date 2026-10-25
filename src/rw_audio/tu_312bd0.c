#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 (*D_003CEC68)();
extern s32 (*D_003CEC6C)();

/* Medium-confidence bank/stream TU: call and shared-data edges. */

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00312BD0);

void func_00312C48(s32 arg0) {
    D_003CEC68(arg0 + 0x40);
}

void func_00312C70(void) {
    D_003CEC6C();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00312C98);
