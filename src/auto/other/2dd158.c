#include "auto/prelude.h"

extern s32 func_002E7610();
extern M2C_UNK D_004510F0;
extern M2C_UNK func_002DCA40;
extern M2C_UNK * D_00451200;
extern M2C_UNK D_003E5E40;

void func_002DD158(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E7610(&D_004510F0, "CScriptManager", &func_002DCA40, 0, 0, 0);
            return;
        }
        D_00451200 = &D_003E5E40;
    }
}
