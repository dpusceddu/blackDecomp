#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002DFEB0();
extern M2C_UNK D_00450DA0;
extern M2C_UNK func_002DA040;
extern M2C_UNK * D_00450EB0;
extern M2C_UNK D_003E3D38;
extern s32 D_00450EB8;
extern s32 D_00450FD8;
extern s32 D_004510F0;

void func_002DA0B0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002DFEB0(&D_00450DA0, "CActionVerticalSpeed", &func_002DA040);
            return;
        }
        D_00450EB0 = &D_003E3D38;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/tu_2da040_2da0b0", func_002DA108);

void func_002DA188(void) {
    func_002DA0B0(1, 0xFFFF);
}

void func_002DA1A8(void) {
    func_002DA0B0(0, 0xFFFF);
}

s32 func_002DA1C8(void) {
    if ((D_00450EB8 == -1) || (D_00450FD8 == -1) || (D_004510F0 == -1)) {
        return 0;
    }
    return 1;
}
