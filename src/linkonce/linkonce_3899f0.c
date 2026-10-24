#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00404890[];
const char rodata_00404890[168] __asm__("D_00404890") __attribute__((aligned(8))) = "Q24Kaim13CActionCrouch" "\000\000" "Q24Kaim7CObject" "\000" "Q24Kaim16CActionAttribute" "\000\000\000\000\000\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim16CActionAttributeZPFv_PQ24Kaim16CActionAttribute" "\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049A9E8;
extern s32 func_00389908();
extern s32 func_00370168();
extern M2C_UNK D_0049A9D8;

s32 * func_003899F0(void) {
    if (D_0049A9E8 == 0) {
        func_00389908();
        func_00370168(&D_0049A9E8, D_00404890, &D_0049A9D8);
    }
    return &D_0049A9E8;
}
