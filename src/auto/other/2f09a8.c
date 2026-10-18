#include "auto/prelude.h"

extern s32 func_002F35B0();
extern M2C_UNK D_00451658;
extern M2C_UNK func_002EEF88;
extern M2C_UNK * D_00451768;
extern M2C_UNK D_003EC200;

void func_002F09A8(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002F35B0(&D_00451658, "CFindNearestData", &func_002EEF88);
            return;
        }
        D_00451768 = &D_003EC200;
    }
}
