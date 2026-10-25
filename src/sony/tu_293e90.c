#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00293E90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00293F60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00294198);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00294260);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00294418);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002946D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00294840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00294A08);

s32 func_00294AB8(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00294AC0);

s32 func_00294B98(void *arg0) {
    return *M2C_FIELD(arg0, s32 **, 0x40);
}


s32 func_00294D30(void *arg0) {
    void *temp_2;
    void *temp_2_2;
    void *temp_2_3;
    void *temp_2_4;
    void *temp_2_5;
    void *temp_2_6;
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x40);
    temp_2 = M2C_FIELD(temp_3, void **, 0x1C8);
    if (temp_2 != NULL) {
        M2C_FIELD(temp_2, s32 *, 0x28) = 0;
    }
    temp_2_2 = M2C_FIELD(temp_3, void **, 0x1D8);
    if (temp_2_2 != NULL) {
        M2C_FIELD(temp_2_2, s32 *, 0x28) = 0;
    }
    temp_2_3 = M2C_FIELD(temp_3, void **, 0x1E8);
    if (temp_2_3 != NULL) {
        M2C_FIELD(temp_2_3, s32 *, 0x28) = 0;
    }
    temp_2_4 = M2C_FIELD(temp_3, void **, 0x1CC);
    if (temp_2_4 != NULL) {
        M2C_FIELD(temp_2_4, s32 *, 0x28) = 0;
    }
    temp_2_5 = M2C_FIELD(temp_3, void **, 0x1DC);
    if (temp_2_5 != NULL) {
        M2C_FIELD(temp_2_5, s32 *, 0x28) = 0;
    }
    temp_2_6 = M2C_FIELD(temp_3, void **, 0x1EC);
    if (temp_2_6 != NULL) {
        M2C_FIELD(temp_2_6, s32 *, 0x28) = 0;
    }
    return 1;
}
