#include "auto/prelude.h"

extern char D_00407700[];
const char rodata_00407700[144] __asm__("D_00407700") __attribute__((aligned(8))) = "Q24Kaim13CGraphManager" "\000\000" "Q24Kaim13CWorldService" "\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim13CWorldServiceZPFv_PQ24Kaim13CWorldService" "\000\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049BC00;
extern s32 * func_0038AFB8();
extern s32 func_00370168();
extern s32 D_0049AB88;

s32 * func_00390C98(void) {
    if (D_0049BC00 == 0) {
        func_0038AFB8();
        func_00370168(&D_0049BC00, D_00407700, &D_0049AB88);
    }
    return &D_0049BC00;
}
