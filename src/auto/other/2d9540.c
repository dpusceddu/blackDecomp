#include "auto/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_004505F8;
extern M2C_UNK func_002D94C8;
extern M2C_UNK * D_00450708;
extern M2C_UNK D_003E4728;

void func_002D9540(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_004505F8, "CEntityTeamSide", &func_002D94C8);
            return;
        }
        D_00450708 = &D_003E4728;
    }
}
