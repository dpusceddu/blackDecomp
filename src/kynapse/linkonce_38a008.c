#include "ps2/prelude.h"

extern char D_00404D40[];
const char rodata_00404D40[96] __asm__("D_00404D40") __attribute__((aligned(8))) = "Q24Kaimt10CMetaClass2ZQ24Kaim16CEntityAttributeZPFv_PQ24Kaim16CEntityAttribute" "\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0040EBD8;
extern s32 func_00370188();

s32 * func_0038A008(void) {
    if (D_0040EBD8 == 0) {
        func_00370188(&D_0040EBD8, D_00404D40);
    }
    return &D_0040EBD8;
}
