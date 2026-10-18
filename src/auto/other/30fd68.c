#include "auto/prelude.h"

extern s32 func_002E75D0();
extern M2C_UNK D_00455E18;
extern M2C_UNK func_0030EA38;
extern M2C_UNK * D_00455F28;
extern M2C_UNK D_003E00E0;

void func_0030FD68(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E75D0(&D_00455E18, "CEntityManager", &func_0030EA38, 0, 1, 1);
            return;
        }
        D_00455F28 = &D_003E00E0;
    }
}
