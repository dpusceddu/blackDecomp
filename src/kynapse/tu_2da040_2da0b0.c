#include "auto/prelude.h"

extern s32 func_002DFEB0();
extern M2C_UNK D_00450DA0;
extern M2C_UNK func_002DA040;
extern M2C_UNK * D_00450EB0;
extern M2C_UNK D_003E3D38;

void func_002DA0B0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002DFEB0(&D_00450DA0, "CActionVerticalSpeed", &func_002DA040);
            return;
        }
        D_00450EB0 = &D_003E3D38;
    }
}
