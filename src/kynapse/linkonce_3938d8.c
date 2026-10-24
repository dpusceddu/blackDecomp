#include "ps2/prelude.h"

extern char D_004083F0[];
const char rodata_004083F0[112] __asm__("D_004083F0") __attribute__((aligned(8))) = "Q24Kaim11CPathFinder" "\000\000\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim13CBrainServiceZPFPQ24Kaim6CBrain_PQ24Kaim13CBrainService" "\000\000";
extern s32 D_0049BD60;
extern s32 func_0038D280();
extern s32 func_00370168();
extern s32 D_0049B940;

s32 * func_003938D8(void) {
    if (D_0049BD60 == 0) {
        func_0038D280();
        func_00370168(&D_0049BD60, D_004083F0, &D_0049B940);
    }
    return &D_0049BD60;
}
