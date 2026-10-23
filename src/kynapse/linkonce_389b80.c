#include "auto/prelude.h"

extern char D_00404A00[];
const char rodata_00404A00[168] __asm__("D_00404A00") __attribute__((aligned(8))) = "Q24Kaim13CActionRotate" "\000\000" "Q24Kaim7CObject" "\000" "Q24Kaim16CActionAttribute" "\000\000\000\000\000\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim16CActionAttributeZPFv_PQ24Kaim16CActionAttribute" "\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049AA08;
extern s32 func_00389908();
extern s32 func_00370168();
extern M2C_UNK D_0049A9D8;

s32 * func_00389B80(void) {
    if (D_0049AA08 == 0) {
        func_00389908();
        func_00370168(&D_0049AA08, D_00404A00, &D_0049A9D8);
    }
    return &D_0049AA08;
}
