#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_004077B8[];
extern char D_004077C8[];
const char rodata_004077B8[16] __asm__("D_004077B8") __attribute__((aligned(8))) = "Q24Kaim7CObject" "\000";
const char rodata_004077C8[144] __asm__("D_004077C8") __attribute__((aligned(8))) = "Q24Kaim22CPointContainerWrapper" "\000" "Q24Kaimt10CMetaClass2ZQ24Kaim22CPointContainerWrapperZPFv_PQ24Kaim22CPointContainerWrapper" "\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049BC20;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern s32 func_00370168();

s32 * func_00390E48(void) {
    if (D_0049BC20 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, D_004077B8);
        }
        func_00370168(&D_0049BC20, D_004077C8, &D_0040EBC0);
    }
    return &D_0049BC20;
}
