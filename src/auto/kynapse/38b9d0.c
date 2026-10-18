#include "auto/prelude.h"

extern char D_00405F48[];
const char rodata_00405F48[160] __asm__("D_00405F48") __attribute__((aligned(8))) = "Q24Kaimt10CMetaClass2ZQ24Kaim7CActionZPFv_PQ24Kaim7CAction" "\000\000\000\000\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim16CActionAttributeZPFv_PQ24Kaim16CActionAttribute" "\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0040EBE8;
extern s32 func_00370188();

s32 * func_0038B9D0(void) {
    if (D_0040EBE8 == 0) {
        func_00370188(&D_0040EBE8, D_00405F48);
    }
    return &D_0040EBE8;
}
