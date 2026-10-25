#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0035D1A0(M2C_UNK *, s32, M2C_UNK);
extern s32 func_00108A20();

void func_0020CA70(void) {

}

f32 func_0020CA78(void) {
    return 0.0f;
}

f32 func_0020CA88(void) {
    return 0.0f;
}

void func_0020CA98(s32 arg0) {
    func_0035D1A0(arg0 + 0x38BC, func_00108A20(), 3);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_20ca70", func_0020CAD0);
