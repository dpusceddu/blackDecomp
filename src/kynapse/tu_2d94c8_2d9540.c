#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_004505F8;
extern M2C_UNK func_002D94C8;
extern M2C_UNK * D_00450708;
extern M2C_UNK D_003E4728;

void func_002D9540(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_004505F8, "CEntityTeamSide", &func_002D94C8);
            return;
        }
        D_00450708 = &D_003E4728;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D9598);

void func_002D9610(void) {
    func_002D9540(1, 0xFFFF);
}

void func_002D9630(void) {
    func_002D9540(0, 0xFFFF);
}
