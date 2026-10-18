#include "auto/prelude.h"

extern char D_00407EB8[];
const char rodata_00407EB8[32] __asm__("D_00407EB8") __attribute__((aligned(8))) = "CAstarData" "\000\000\000\000\000\000" "Q24Kaim7CObject" "\000";
extern s32 func_002F35B0();
extern M2C_UNK D_00454788;
extern M2C_UNK func_002FD998;
extern M2C_UNK * D_00454898;
extern M2C_UNK D_003EC200;

void func_002FEA88(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002F35B0(&D_00454788, D_00407EB8, &func_002FD998);
            return;
        }
        D_00454898 = &D_003EC200;
    }
}
