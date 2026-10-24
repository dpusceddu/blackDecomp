#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 * func_00123C90();
extern M2C_UNK D_0048EFA8;
extern s32 func_001050A8();
extern void * D_0040F0E0;
extern s32 func_001050A8(void *, M2C_UNK);
extern u8 * D_0040F544;
extern s32 func_0035CBC0();

void func_00103B38(void) {
    s32 temp_16;
    s32 temp_17;
    s32 temp_17_2;

    temp_17 = *func_00123C90(&D_0048EFA8, 0, 0);
    if ((temp_17 != -1) || (temp_16 = *func_00123C90(&D_0048EFA8, 0, 1), (temp_16 != temp_17)) || (temp_17_2 = *func_00123C90(&D_0048EFA8, 0, 2), (temp_17_2 != temp_16)) || (*func_00123C90(&D_0048EFA8, 0, 3) != temp_17_2)) {
        func_001050A8(D_0040F0E0 + 0x20220, 0);
    }
}

void func_00103BF8(void) {
    func_001050A8(D_0040F0E0 + 0x20220, 0);
}

void func_00103C28(void) {
    s32 temp_16;
    s32 temp_17;
    s32 temp_17_2;
    u8 *temp_16_2;

    temp_17 = *func_00123C90(&D_0048EFA8, 0, 0);
    if ((temp_17 != -1) || (temp_16 = *func_00123C90(&D_0048EFA8, 0, 1), (temp_16 != temp_17)) || (temp_17_2 = *func_00123C90(&D_0048EFA8, 0, 2), (temp_17_2 != temp_16)) || (*func_00123C90(&D_0048EFA8, 0, 3) != temp_17_2)) {
        temp_16_2 = D_0040F544;
        func_0035CBC0(temp_16_2 + 0x3820, "BlackIntroSequence");
        if (M2C_FIELD(temp_16_2, s8 *, 0x3840) == 0) {
            M2C_FIELD(temp_16_2, s32 *, 0x388C) = 1;
            return;
        }
        M2C_FIELD(temp_16_2, s32 *, 0x3884) = 1;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00103D00);
