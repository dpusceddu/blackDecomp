#include "auto/prelude.h"

extern s32 func_002E00F0();
extern M2C_UNK D_0044F248;
extern M2C_UNK func_002D65E8;
extern M2C_UNK * D_0044F358;
extern M2C_UNK D_003E2AE0;

void func_002D6FA8(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E00F0(&D_0044F248, "CShooterAgent", &func_002D65E8, 0, 0, 0);
            return;
        }
        D_0044F358 = &D_003E2AE0;
    }
}
