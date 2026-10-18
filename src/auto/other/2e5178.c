#include "auto/prelude.h"

extern char D_00406550[];
const char rodata_00406550[32] __asm__("D_00406550") __attribute__((aligned(8))) = "IPathFinder" "\000\000\000\000\000" "Q24Kaim7CObject" "\000";
extern s32 func_002E75D0();
extern M2C_UNK D_004512B0;
extern M2C_UNK * D_004513C0;
extern M2C_UNK D_003E00E0;

void func_002E5178(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E75D0(&D_004512B0, D_00406550, NULL, 0, 0, 0);
            return;
        }
        D_004513C0 = &D_003E00E0;
    }
}
