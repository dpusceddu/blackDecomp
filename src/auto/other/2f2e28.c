#include "auto/prelude.h"

extern s32 func_002E7610();
extern M2C_UNK D_00452158;
extern M2C_UNK func_002F2438;
extern M2C_UNK * D_00452268;
extern M2C_UNK D_003E5E40;

void func_002F2E28(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E7610(&D_00452158, "CGraphManager", &func_002F2438, 0, 0, 0);
            return;
        }
        D_00452268 = &D_003E5E40;
    }
}
