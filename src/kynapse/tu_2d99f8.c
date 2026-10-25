#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_00450940;
extern M2C_UNK func_002D99F8;
extern M2C_UNK * D_00450A50;
extern M2C_UNK D_003E4728;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/tu_2d99f8", func_002D99F8);

void func_002D9A90(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_00450940, "CEntityWidth", &func_002D99F8);
            return;
        }
        D_00450A50 = &D_003E4728;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/tu_2d99f8", func_002D9AE8);

void func_002D9B58(void) {
    func_002D9A90(1, 0xFFFF);
}

void func_002D9B78(void) {
    func_002D9A90(0, 0xFFFF);
}
