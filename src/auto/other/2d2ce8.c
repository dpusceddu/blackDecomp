#include "auto/prelude.h"

extern s32 func_002E00F0();
extern M2C_UNK D_0044ECD0;
extern M2C_UNK func_002D1610;
extern M2C_UNK * D_0044EDE0;
extern M2C_UNK D_003E2AE0;

void func_002D2CE8(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E00F0(&D_0044ECD0, "CFleeAgent", &func_002D1610, 0, 0, 0);
            return;
        }
        D_0044EDE0 = &D_003E2AE0;
    }
}
