#include "auto/prelude.h"

extern char D_00406AC8[];
const char rodata_00406AC8[112] __asm__("D_00406AC8") __attribute__((aligned(8))) = "Q24Kaimt10CMetaClass2ZQ24Kaim22CPointContainerWrapperZPFv_PQ24Kaim22CPointContainerWrapper" "\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0040EC18;
extern s32 func_00370188();

s32 * func_0038E5F8(void) {
    if (D_0040EC18 == 0) {
        func_00370188(&D_0040EC18, D_00406AC8);
    }
    return &D_0040EC18;
}
