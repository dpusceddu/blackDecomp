#include "include_asm.h"
#include "ps2/prelude.h"

extern u32 func_0035CA74(s32, s32);
extern s32 func_00370DA8();
extern M2C_UNK func_003714B0;
extern M2C_UNK func_00370760;
extern char D_0040C0E0[];
const u32 rodata_0040C0E0[4] __asm__("D_0040C0E0") __attribute__((aligned(8))) = { 0x00000000, 0x003714B0, 0x00000000, 0x00371500 };

u32 func_003707A0(s32 *arg0, s32 *arg1) {
    return func_0035CA74(*arg0, *arg1) >> 0x1F;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/libc/tu_3707a0", func_003707C8);

s32 func_00370C90(void *arg0) {
    s32 var_2;
    void *temp_2;

    var_2 = 0;
    if (arg0 != NULL) {
        temp_2 = M2C_FIELD(arg0, void **, 4);
        var_2 = func_00370DA8(M2C_FIELD(temp_2, s32 *, 4), &func_003714B0, 1, arg0 + M2C_FIELD(temp_2, s16 *, 0), &func_00370760, arg0);
    }
    return var_2 != 0;
}

void func_00370CE0(void *arg0, s32 arg1, s32 arg2) {
    if (arg0 != NULL) {
        M2C_FIELD(arg0, s32 *, 8) = arg2;
        M2C_FIELD(arg0, s32 *, 0) = arg1;
        M2C_FIELD(arg0, M2C_UNK **, 4) = &D_0040C0E0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/libc/tu_3707a0", func_00370D00);
