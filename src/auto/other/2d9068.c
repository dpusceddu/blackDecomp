#include "auto/prelude.h"

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
