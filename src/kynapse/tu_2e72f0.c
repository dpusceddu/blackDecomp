#include "auto/prelude.h"

extern char D_00406A00[];
const char rodata_00406A00[40] __asm__("D_00406A00") __attribute__((aligned(8))) = "CNearestPoint" "\000\000\000" "Q24Kaim13CPointWrapper" "\000\000";
extern s32 func_0038E108();
extern M2C_UNK D_004513D8;
extern M2C_UNK D_003EA778;
extern M2C_UNK * D_004514E8;
extern M2C_UNK D_003EA790;

void func_002E72F0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_0038E108(&D_004513D8, D_00406A00, 0, 0, 0, 0);
            M2C_FIELD(&D_004513D8, M2C_UNK **, 0x110) = &D_003EA778;
            return;
        }
        D_004514E8 = &D_003EA790;
    }
}
