#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_003BE7A8;
extern void func_00215788(M2C_UNK);

void func_0020E840(void) {
    if (D_003BE7A8 == 2) {
        func_00215788(0);
    }
    D_003BE7A8 = 1;
}

void func_0020E880(void) {
    if (D_003BE7A8 == 2) {
        func_00215788(0);
    }
    D_003BE7A8 = 1;
}

void func_0020E8C0(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_20e840", func_0020E8C8);
