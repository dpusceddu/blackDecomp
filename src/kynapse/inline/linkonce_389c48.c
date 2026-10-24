#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00404AB8[];
const char rodata_00404AB8[168] __asm__("D_00404AB8") __attribute__((aligned(8))) = "Q24Kaim12CActionShoot" "\000\000\000" "Q24Kaim7CObject" "\000" "Q24Kaim16CActionAttribute" "\000\000\000\000\000\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim16CActionAttributeZPFv_PQ24Kaim16CActionAttribute" "\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049AA18;
extern s32 func_00389908();
extern s32 func_00370168();
extern M2C_UNK D_0049A9D8;

s32 * func_00389C48(void) {
    if (D_0049AA18 == 0) {
        func_00389908();
        func_00370168(&D_0049AA18, D_00404AB8, &D_0049A9D8);
    }
    return &D_0049AA18;
}
