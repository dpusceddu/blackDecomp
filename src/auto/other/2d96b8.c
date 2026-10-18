#include "auto/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_00450710;
extern M2C_UNK func_002D9650;
extern M2C_UNK * D_00450820;
extern M2C_UNK D_003E4728;

void func_002D96B8(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_00450710, "CEntityTorsoOrientation", &func_002D9650);
            return;
        }
        D_00450820 = &D_003E4728;
    }
}
