#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00177800();
extern s32 func_001779D0();

s32 func_001771E0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x978) = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001771F0);

void func_00177238(void) {
    func_00177800();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00177258);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00177350);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00177470);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001776A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00177750);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00177780);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001777D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00177800);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001778A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00177930);

void * func_00177988(void *arg0) {
    if (func_001779D0() != 0) {
        return NULL;
    }
    return arg0 + (M2C_FIELD(arg0, s32 *, 0x960) * 8);
}

s32 func_001779C0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x968) == 0x12C;
}

s32 func_001779D0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x968) == 0;
}

s32 func_001779E0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x968);
}
