#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002DFEB0();
extern M2C_UNK D_0044F6A8;
extern M2C_UNK func_002D7C80;
extern M2C_UNK * D_0044F7B8;
extern M2C_UNK D_003E3D38;

void func_002D7CF0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002DFEB0(&D_0044F6A8, "CActionJump", &func_002D7C80);
            return;
        }
        D_0044F7B8 = &D_003E3D38;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D7D48);

void func_002D7DC8(void) {
    func_002D7CF0(1, 0xFFFF);
}

void func_002D7DE8(void) {
    func_002D7CF0(0, 0xFFFF);
}
