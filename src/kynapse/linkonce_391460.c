#include "ps2/prelude.h"

extern char D_00407B28[];
const char rodata_00407B28[152] __asm__("D_00407B28") __attribute__((aligned(8))) = "Q24Kaim18CPathObjectManager" "\000\000\000\000\000" "Q24Kaim13CWorldService" "\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim13CWorldServiceZPFv_PQ24Kaim13CWorldService" "\000\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049BC80;
extern s32 * func_0038AFB8();
extern s32 func_00370168();
extern s32 D_0049AB88;

s32 * func_00391460(void) {
    if (D_0049BC80 == 0) {
        func_0038AFB8();
        func_00370168(&D_0049BC80, D_00407B28, &D_0049AB88);
    }
    return &D_0049BC80;
}
