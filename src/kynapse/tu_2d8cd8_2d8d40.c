#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_00450080;
extern M2C_UNK func_002D8CD8;
extern M2C_UNK * D_00450190;
extern M2C_UNK D_003E4728;

void func_002D8D40(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_00450080, "CEntityHearingAcuteness", &func_002D8CD8);
            return;
        }
        D_00450190 = &D_003E4728;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D8D98);

void func_002D8E20(void) {
    func_002D8D40(1, 0xFFFF);
}

void func_002D8E40(void) {
    func_002D8D40(0, 0xFFFF);
}
