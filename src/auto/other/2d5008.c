#include "auto/prelude.h"

extern char D_00404400[];
const char rodata_00404400[56] __asm__("D_00404400") __attribute__((aligned(8))) = "CHideAgent" "\000\000\000\000\000\000" "Q24Kaim7CObject" "\000" "Q24Kaim11CGraphPoint" "\000\000\000\000";
extern s32 func_002E00F0();
extern M2C_UNK D_0044F018;
extern M2C_UNK func_002D3C90;
extern M2C_UNK * D_0044F128;
extern M2C_UNK D_003E2AE0;

void func_002D5008(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E00F0(&D_0044F018, D_00404400, &func_002D3C90, 0, 0, 0);
            return;
        }
        D_0044F128 = &D_003E2AE0;
    }
}
