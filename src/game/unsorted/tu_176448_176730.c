#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00176460(void *);

s32 func_00176730(void *arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = (s8) arg1 * 0x1C;
    M2C_FIELD((arg0 + temp_5), s8 *, 0xE8) = 0;
    return func_00176460(arg0 + (temp_5 + 0xD0));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176768);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176770);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_001768D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176978);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176A78);

f32 func_00176AE0(void) {
    return 0.0f;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176AF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176B50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176BB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176C70);

void func_00176D00(void) {

}

void func_00176D08(void) {

}

void func_00176D10(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176D18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176D90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176DD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176E40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176EA0);
