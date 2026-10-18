#include "auto/prelude.h"

extern s32 func_002E4D88();
extern M2C_UNK D_004524A0;
extern M2C_UNK * D_004525B0;
extern M2C_UNK D_003E00F8;

void func_002F49F0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4D88(&D_004524A0, "CPathObject", 0, 0);
            return;
        }
        D_004525B0 = &D_003E00F8;
    }
}
