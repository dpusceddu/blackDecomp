#include "auto/prelude.h"

extern char D_00406210[];
const char rodata_00406210[112] __asm__("D_00406210") __attribute__((aligned(8))) = "Q24Kaimt10CMetaClass2ZQ24Kaim6CBrainZPFPQ24Kaim7CEntityRQ24Kaim12CActionClass_PQ24Kaim6CBrain" "\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0040EBF0;
extern s32 func_00370188();

s32 * func_0038C7A8(void) {
    if (D_0040EBF0 == 0) {
        func_00370188(&D_0040EBF0, D_00406210);
    }
    return &D_0040EBF0;
}
