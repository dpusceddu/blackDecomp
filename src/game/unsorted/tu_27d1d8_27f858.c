#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0027F890();
extern s32 func_0027FA68(M2C_UNK, M2C_UNK);

void func_0027F858(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x28) != 0) {
        func_0027F890();
        M2C_FIELD(arg0, u8 *, 0x28) = 0U;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8_27f858", func_0027F890);

void func_0027F9C0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x24) = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8_27f858", func_0027F9C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8_27f858", func_0027FA58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8_27f858", func_0027FA68);

void func_0027FBA0(void) {
    func_0027FA68(1, 0xFFFF);
}
