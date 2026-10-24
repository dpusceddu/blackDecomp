#include "ps2/prelude.h"

extern char D_00404820[];
const char rodata_00404820[96] __asm__("D_00404820") __attribute__((aligned(8))) = "Q24Kaimt10CMetaClass2ZQ24Kaim16CActionAttributeZPFv_PQ24Kaim16CActionAttribute" "\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0040EBD0;
extern s32 func_00370188();

s32 * func_00389980(void) {
    if (D_0040EBD0 == 0) {
        func_00370188(&D_0040EBD0, D_00404820);
    }
    return &D_0040EBD0;
}
