#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00296468();
extern s32 func_00371610(s32);
extern s32 func_003716F8(s32);

void func_00294E98(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 8);
}

void func_00294EA8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0xC);
}

s32 func_00294EB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_2;
    u32 temp_4;

    temp_2 = ((u32) ((M2C_FIELD(arg1, u32 *, 8) + arg3) - 1) / (u32) arg3) * arg3;
    temp_4 = temp_2 + arg2;
    if ((u32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 4)) < temp_4) {
        func_00296468(arg0, (s32) "work area size is too small");
        return 0;
    }
    M2C_FIELD(arg1, u32 *, 8) = temp_4;
    return temp_2;
}

s32 func_00294F28(void *arg0) {
    func_00371610(M2C_FIELD(arg0, s32 *, 0x40) + 0x68);
    return 1;
}

s32 func_00294F50(void *arg0) {
    func_003716F8(M2C_FIELD(arg0, s32 *, 0x40) + 0x68);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_293e90_294e98", func_00294F78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_293e90_294e98", func_00295208);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_293e90_294e98", func_002954C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_293e90_294e98", func_002958E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_293e90_294e98", func_002959A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_293e90_294e98", func_00295A38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_293e90_294e98", func_00295BF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_293e90_294e98", func_002960D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_293e90_294e98", func_00296218);
