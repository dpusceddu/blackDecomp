#include "ps2/prelude.h"

extern char D_00405A88[];
const char rodata_00405A88[96] __asm__("D_00405A88") __attribute__((aligned(8))) = "Q24Kaimt10CMetaClass2ZQ24Kaim13CWorldServiceZPFv_PQ24Kaim13CWorldService" "\000\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0040EBE0;
extern s32 func_00370188();

s32 * func_0038B008(void) {
    if (D_0040EBE0 == 0) {
        func_00370188(&D_0040EBE0, D_00405A88);
    }
    return &D_0040EBE0;
}
