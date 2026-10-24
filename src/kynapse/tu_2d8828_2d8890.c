#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_0044FD38;
extern M2C_UNK func_002D8828;
extern M2C_UNK * D_0044FE48;
extern M2C_UNK D_003E4728;

void func_002D8890(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_0044FD38, "CEntityEyePosition", &func_002D8828);
            return;
        }
        D_0044FE48 = &D_003E4728;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D88E8);

void func_002D8978(void) {
    func_002D8890(1, 0xFFFF);
}

void func_002D8998(void) {
    func_002D8890(0, 0xFFFF);
}
