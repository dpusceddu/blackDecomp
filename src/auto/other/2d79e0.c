#include "auto/prelude.h"

extern s32 func_002DFEB0();
extern M2C_UNK D_0044F478;
extern M2C_UNK func_002D7970;
extern M2C_UNK * D_0044F588;
extern M2C_UNK D_003E3D38;

void func_002D79E0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002DFEB0(&D_0044F478, "CActionAcceleration", &func_002D7970);
            return;
        }
        D_0044F588 = &D_003E3D38;
    }
}
