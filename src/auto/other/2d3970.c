#include "auto/prelude.h"

extern s32 func_002E00F0();
extern M2C_UNK D_0044EF00;
extern M2C_UNK func_002D38C8;
extern M2C_UNK * D_0044F010;
extern M2C_UNK D_003E2AE0;

void func_002D3970(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E00F0(&D_0044EF00, "CGotoAgent", &func_002D38C8, 0, 0, 0);
            return;
        }
        D_0044F010 = &D_003E2AE0;
    }
}
