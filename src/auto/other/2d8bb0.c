#include "auto/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_0044FF68;
extern M2C_UNK func_002D8B48;
extern M2C_UNK * D_00450078;
extern M2C_UNK D_003E4728;

void func_002D8BB0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_0044FF68, "CEntityHeadDirection", &func_002D8B48);
            return;
        }
        D_00450078 = &D_003E4728;
    }
}
