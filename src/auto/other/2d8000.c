#include "auto/prelude.h"

extern s32 func_002DFEB0();
extern M2C_UNK D_0044F8D8;
extern M2C_UNK func_002D7F90;
extern M2C_UNK * D_0044F9E8;
extern M2C_UNK D_003E3D38;

void func_002D8000(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002DFEB0(&D_0044F8D8, "CActionShoot", &func_002D7F90);
            return;
        }
        D_0044F9E8 = &D_003E3D38;
    }
}
