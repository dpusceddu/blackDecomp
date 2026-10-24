#include "include_asm.h"
#include "ps2/prelude.h"

extern u32 func_003429E8(s32);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003420E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00342390);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00342478);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003425E0);

u32 func_003426A8(s32 arg0, s32 arg1) {
    return func_003429E8(arg1) >> 0x16;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003426C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00342758);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00342788);

#include "ps2/recovered_types.h"
extern s32 func_00342938(void *, void *);

s32 func_003428C8(void *arg0, s32 arg1) {
    void *temp_16;
    void *temp_3;

    temp_16 = M2C_FIELD(arg0, void **, 0x14);
    temp_3 = M2C_FIELD(temp_16, void **, 0);
    M2C_FIELD(arg0, void **, 0x14) = temp_3;
    M2C_FIELD(temp_3, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0x1030) = (s32) (M2C_FIELD(arg0, s32 *, 0x1030) - 1);
    M2C_FIELD(temp_16, s32 *, 4) = 0;
    M2C_FIELD(temp_16, void **, 0) = (void *) M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), void **, 4) = temp_16;
    M2C_FIELD(arg0, void **, 0x10) = temp_16;
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) + 1);
    func_00342938(arg0, temp_16);
    return M2C_FIELD(temp_16, s32 *, 0x1C);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00342938);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003429B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003429E8);
