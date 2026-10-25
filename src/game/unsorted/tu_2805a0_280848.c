#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_00281948(s32 arg0, s32 arg1);

void func_00280848(void *arg0) {
    func_00281948(arg0 + 0xB308, 0);
    M2C_FIELD(arg0, s8 *, 0xCB9E) = 0;
}

u8 func_00280888(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0xCB9E);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280848", func_00280898);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280848", func_002808A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280848", func_00280908);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280848", func_002809F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280848", func_00280A08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280848", func_00280A38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280848", func_00280A80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280848", func_00280B10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280848", func_00280BC0);
