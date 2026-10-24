#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002DFEB0();
extern M2C_UNK D_0044F7C0;
extern M2C_UNK func_002D7E08;
extern M2C_UNK * D_0044F8D0;
extern M2C_UNK D_003E3D38;

void func_002D7E78(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002DFEB0(&D_0044F7C0, "CActionRotate", &func_002D7E08);
            return;
        }
        D_0044F8D0 = &D_003E3D38;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D7ED0);

void func_002D7F50(void) {
    func_002D7E78(1, 0xFFFF);
}

void func_002D7F70(void) {
    func_002D7E78(0, 0xFFFF);
}
