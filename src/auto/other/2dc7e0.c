#include "auto/prelude.h"

extern s32 func_002E7610();
extern M2C_UNK D_00450FD8;
extern M2C_UNK func_002DAD10;
extern M2C_UNK * D_004510E8;
extern M2C_UNK D_003E5E40;

void func_002DC7E0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E7610(&D_00450FD8, "CPointMapper", &func_002DAD10, 0, 0, 0);
            return;
        }
        D_004510E8 = &D_003E5E40;
    }
}
