#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_001E9EE8();
extern M2C_UNK D_0042A630;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E9D30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E9E08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E9EE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EA200);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EA2D0);

s32 func_001EA4F0(s32 arg0) {
    func_001E9EE8(arg0, 0);
    return 1;
}

void func_001EA510(void) {

}

void func_001EA518(void *arg0, s32 arg1, s32 arg2) {
    void *temp_4;

    if (arg2 != 0) {
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) | (1 << arg1));
        temp_4 = (arg1 * 0x140) + ((s32) &D_0042A630);
        M2C_FIELD(temp_4, f32 *, 0x138) = -1.0f;
        M2C_FIELD(temp_4, s8 *, 0x13D) = 0;
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) & ~(1 << arg1));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EA580);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EA620);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EA628);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EA728);
