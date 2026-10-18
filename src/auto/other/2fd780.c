#include "auto/prelude.h"

extern char D_00407D58[];
const char rodata_00407D58[32] __asm__("D_00407D58") __attribute__((aligned(8))) = "CAccessWaysData" "\000" "Q24Kaim7CObject" "\000";
extern s32 func_002F35B0();
extern M2C_UNK D_00454670;
extern M2C_UNK func_002FCAA8;
extern M2C_UNK * D_00454780;
extern M2C_UNK D_003EC200;

void func_002FD780(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002F35B0(&D_00454670, D_00407D58, &func_002FCAA8);
            return;
        }
        D_00454780 = &D_003EC200;
    }
}
