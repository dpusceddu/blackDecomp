#include "auto/prelude.h"

extern char D_00407900[];
const char rodata_00407900[32] __asm__("D_00407900") __attribute__((aligned(8))) = "CPathCostData" "\000\000\000" "Q24Kaim7CObject" "\000";
extern s32 func_002F35B0();
extern M2C_UNK D_00452388;
extern M2C_UNK func_002F3600;
extern M2C_UNK * D_00452498;
extern M2C_UNK D_003EC200;

void func_002F4260(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002F35B0(&D_00452388, D_00407900, &func_002F3600);
            return;
        }
        D_00452498 = &D_003EC200;
    }
}
