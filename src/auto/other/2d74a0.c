#include "auto/prelude.h"

extern char D_004046F8[];
const char rodata_004046F8[56] __asm__("D_004046F8") __attribute__((aligned(8))) = "CWanderAgent" "\000\000\000\000" "Q24Kaim7CObject" "\000" "Q24Kaim11CGraphPoint" "\000\000\000\000";
extern s32 func_002E00F0();
extern M2C_UNK D_0044F360;
extern M2C_UNK func_002D7260;
extern M2C_UNK * D_0044F470;
extern M2C_UNK D_003E2AE0;

void func_002D74A0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E00F0(&D_0044F360, D_004046F8, &func_002D7260, 0, 0, 0);
            return;
        }
        D_0044F470 = &D_003E2AE0;
    }
}
