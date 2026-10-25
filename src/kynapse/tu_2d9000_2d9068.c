#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_004502B0;
extern M2C_UNK func_002D9000;
extern M2C_UNK * D_004503C0;
extern M2C_UNK D_003E4728;

void func_002D9068(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_004502B0, "CEntityKneePosition", &func_002D9000);
            return;
        }
        D_004503C0 = &D_003E4728;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/tu_2d9000_2d9068", func_002D90C0);

void func_002D9150(void) {
    func_002D9068(1, 0xFFFF);
}

void func_002D9170(void) {
    func_002D9068(0, 0xFFFF);
}
