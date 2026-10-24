#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00405870[];
const char rodata_00405870[176] __asm__("D_00405870") __attribute__((aligned(8))) = "Q24Kaim18CActionTorsoRotate" "\000\000\000\000\000" "Q24Kaim7CObject" "\000" "Q24Kaim16CActionAttribute" "\000\000\000\000\000\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim16CActionAttributeZPFv_PQ24Kaim16CActionAttribute" "\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049AB48;
extern s32 func_00389908();
extern s32 func_00370168();
extern M2C_UNK D_0049A9D8;

s32 * func_0038AD30(void) {
    if (D_0049AB48 == 0) {
        func_00389908();
        func_00370168(&D_0049AB48, D_00405870, &D_0049A9D8);
    }
    return &D_0049AB48;
}
