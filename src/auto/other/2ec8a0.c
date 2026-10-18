#include "auto/prelude.h"

extern s32 func_0038F000();
extern M2C_UNK D_00451540;
extern M2C_UNK func_002EC918;
extern M2C_UNK D_003EBB30;
extern M2C_UNK * D_00451650;
extern M2C_UNK D_003EBB48;

void func_002EC8A0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_0038F000(&D_00451540, "CTeam", &func_002EC918, 0, 0, 0);
            M2C_FIELD(&D_00451540, M2C_UNK **, 0x110) = &D_003EBB30;
            return;
        }
        D_00451650 = &D_003EBB48;
    }
}
