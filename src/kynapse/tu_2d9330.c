#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_004504E0;
extern M2C_UNK func_002D9330;
extern M2C_UNK * D_004505F0;
extern M2C_UNK D_003E4728;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D9330);

void func_002D93C0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_004504E0, "CEntityMaxSpeed", &func_002D9330);
            return;
        }
        D_004505F0 = &D_003E4728;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D9418);

void func_002D9488(void) {
    func_002D93C0(1, 0xFFFF);
}

void func_002D94A8(void) {
    func_002D93C0(0, 0xFFFF);
}
