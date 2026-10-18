#include "auto/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_00450828;
extern M2C_UNK func_002D97E0;
extern M2C_UNK * D_00450938;
extern M2C_UNK D_003E4728;

void func_002D9880(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_00450828, "CEntityVisualAcuteness", &func_002D97E0);
            return;
        }
        D_00450938 = &D_003E4728;
    }
}
