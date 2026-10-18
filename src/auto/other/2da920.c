#include "auto/prelude.h"

extern s32 func_002E7610();
extern M2C_UNK D_00450EB8;
extern M2C_UNK func_002DA208;
extern M2C_UNK * D_00450FC8;
extern M2C_UNK D_003E5E40;

void func_002DA920(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E7610(&D_00450EB8, "CPathWayManager", &func_002DA208, 0, 0, 0);
            return;
        }
        D_00450FC8 = &D_003E5E40;
    }
}
