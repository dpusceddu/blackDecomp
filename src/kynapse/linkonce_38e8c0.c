#include "ps2/prelude.h"

extern char D_00406BA0[];
const char rodata_00406BA0[216] __asm__("D_00406BA0") __attribute__((aligned(8))) = "Q24Kaim18CWorldServiceClass" "\000\000\000\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim13CBrainServiceZPFPQ24Kaim6CBrain_PQ24Kaim13CBrainService" "\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim13CWorldServiceZPFv_PQ24Kaim13CWorldService" "\000\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049BA60;
extern s32 func_0038B008();
extern s32 func_00370168();
extern s32 D_0040EBE0;

s32 * func_0038E8C0(void) {
    if (D_0049BA60 == 0) {
        func_0038B008();
        func_00370168(&D_0049BA60, D_00406BA0, &D_0040EBE0);
    }
    return &D_0049BA60;
}
