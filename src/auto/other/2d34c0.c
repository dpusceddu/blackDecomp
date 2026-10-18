#include "auto/prelude.h"

extern s32 func_002E00F0();
extern M2C_UNK D_0044EDE8;
extern M2C_UNK func_002D2FF8;
extern M2C_UNK * D_0044EEF8;
extern M2C_UNK D_003E2AE0;

void func_002D34C0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E00F0(&D_0044EDE8, "CFollowerAgent", &func_002D2FF8, 0, 0, 0);
            return;
        }
        D_0044EEF8 = &D_003E2AE0;
    }
}
