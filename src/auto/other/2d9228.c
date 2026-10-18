#include "auto/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_004503C8;
extern M2C_UNK func_002D9190;
extern M2C_UNK * D_004504D8;
extern M2C_UNK D_003E4728;

void func_002D9228(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_004503C8, "CEntityLength", &func_002D9190);
            return;
        }
        D_004504D8 = &D_003E4728;
    }
}
