#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_0044FF68;
extern M2C_UNK func_002D8B48;
extern M2C_UNK * D_00450078;
extern M2C_UNK D_003E4728;

void func_002D8BB0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_0044FF68, "CEntityHeadDirection", &func_002D8B48);
            return;
        }
        D_00450078 = &D_003E4728;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D8C08);

void func_002D8C98(void) {
    func_002D8BB0(1, 0xFFFF);
}

void func_002D8CB8(void) {
    func_002D8BB0(0, 0xFFFF);
}
