#include "auto/prelude.h"

extern char D_00408630[];
const char rodata_00408630[96] __asm__("D_00408630") __attribute__((aligned(8))) = "CRepulsorDynamicAvoidance" "\000\000\000\000\000\000\000" "Q24Kaim7CObject" "\000" "Q34Kaimt8CVarList1ZPQ24Kaim7CEntity9CIterator" "\000\000\000";
extern s32 func_0030D0E0();
extern M2C_UNK D_00455AD0;
extern M2C_UNK func_00305538;
extern M2C_UNK * D_00455BE0;
extern M2C_UNK D_003F07A0;

void func_003063A8(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_0030D0E0(&D_00455AD0, D_00408630, &func_00305538);
            return;
        }
        D_00455BE0 = &D_003F07A0;
    }
}
