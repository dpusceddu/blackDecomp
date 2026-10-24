#include "ps2/prelude.h"

extern char D_00404F48[];
const char rodata_00404F48[176] __asm__("D_00404F48") __attribute__((aligned(8))) = "Q24Kaim20CEntityHeadDirection" "\000\000\000" "Q24Kaim7CObject" "\000" "Q24Kaim16CEntityAttribute" "\000\000\000\000\000\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim16CEntityAttributeZPFv_PQ24Kaim16CEntityAttribute" "\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049AA88;
extern s32 func_00389F90();
extern s32 func_00370168();
extern M2C_UNK D_0049AA58;

s32 * func_0038A268(void) {
    if (D_0049AA88 == 0) {
        func_00389F90();
        func_00370168(&D_0049AA88, D_00404F48, &D_0049AA58);
    }
    return &D_0049AA88;
}
