#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002DFEB0();
extern M2C_UNK D_00450A58;
extern M2C_UNK func_002D9B98;
extern M2C_UNK * D_00450B68;
extern M2C_UNK D_003E3D38;

void func_002D9C08(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002DFEB0(&D_00450A58, "CActionActivate", &func_002D9B98);
            return;
        }
        D_00450B68 = &D_003E3D38;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/tu_2d9b98_2d9c08", func_002D9C60);

void func_002D9CE0(void) {
    func_002D9C08(1, 0xFFFF);
}

void func_002D9D00(void) {
    func_002D9C08(0, 0xFFFF);
}
