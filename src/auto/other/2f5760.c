#include "auto/prelude.h"

extern s32 func_002E7610();
extern M2C_UNK D_004525B8;
extern M2C_UNK func_002F4BC0;
extern M2C_UNK * D_004526C8;
extern M2C_UNK D_003E5E40;

void func_002F5760(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E7610(&D_004525B8, "CPathObjectManager", &func_002F4BC0, 0, 0, 0);
            return;
        }
        D_004526C8 = &D_003E5E40;
    }
}
