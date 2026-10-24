#include "ps2/prelude.h"

extern char D_00406B40[];
const char rodata_00406B40[64] __asm__("D_00406B40") __attribute__((aligned(8))) = "Q24Kaim12CBaseService" "\000\000\000" "Q24Kaim7CObject" "\000" "Q24Kaim13CBrainService" "\000\000";
extern s32 D_0049AB98;
extern s32 func_00389100();
extern s32 func_00370168();
extern M2C_UNK D_0040EBC0;

s32 * func_0038E6E0(void) {
    if (D_0049AB98 == 0) {
        func_00389100();
        func_00370168(&D_0049AB98, D_00406B40, &D_0040EBC0);
    }
    return &D_0049AB98;
}
