#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_268c68", func_00268C68);

s32 func_00268E90(void *arg0, s32 arg1) {
    return M2C_FIELD(arg0, s32 *, 0x114) + (arg1 << 6);
}

void func_00268EA0(void *arg0) {
    s16 temp_6;
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x28);
    temp_6 = M2C_FIELD(temp_3, s16 *, 0x30);
    M2C_FIELD(temp_3, M2C_UNK (**)(void *, M2C_UNK, s16), 0x34)(arg0 + temp_6, 0, temp_6);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_268c68", func_00268ED0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_268c68", func_00269020);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_268c68", func_002690A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_268c68", func_00269188);

s32 func_002694D8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x1C) = 1;
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_268c68", func_002694E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_268c68", func_002696A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_268c68", func_00269718);
