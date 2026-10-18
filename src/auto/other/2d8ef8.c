#include "auto/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_00450198;
extern M2C_UNK func_002D8E60;
extern M2C_UNK * D_004502A8;
extern M2C_UNK D_003E4728;

void func_002D8EF8(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_00450198, "CEntityHeight", &func_002D8E60);
            return;
        }
        D_004502A8 = &D_003E4728;
    }
}
