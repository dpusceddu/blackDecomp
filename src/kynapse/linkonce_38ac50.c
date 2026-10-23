#include "auto/prelude.h"

extern char D_004057A8[];
const char rodata_004057A8[176] __asm__("D_004057A8") __attribute__((aligned(8))) = "Q24Kaim17CActionHeadRotate" "\000\000\000\000\000\000" "Q24Kaim7CObject" "\000" "Q24Kaim16CActionAttribute" "\000\000\000\000\000\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim16CActionAttributeZPFv_PQ24Kaim16CActionAttribute" "\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049AB38;
extern s32 func_00389908();
extern s32 func_00370168();
extern M2C_UNK D_0049A9D8;

s32 * func_0038AC50(void) {
    if (D_0049AB38 == 0) {
        func_00389908();
        func_00370168(&D_0049AB38, D_004057A8, &D_0049A9D8);
    }
    return &D_0049AB38;
}
