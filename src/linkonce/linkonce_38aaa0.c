#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00405628[];
const char rodata_00405628[168] __asm__("D_00405628") __attribute__((aligned(8))) = "Q24Kaim12CEntityWidth" "\000\000\000" "Q24Kaim7CObject" "\000" "Q24Kaim16CEntityAttribute" "\000\000\000\000\000\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim16CEntityAttributeZPFv_PQ24Kaim16CEntityAttribute" "\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049AB18;
extern s32 func_00389F90();
extern s32 func_00370168();
extern M2C_UNK D_0049AA58;

s32 * func_0038AAA0(void) {
    if (D_0049AB18 == 0) {
        func_00389F90();
        func_00370168(&D_0049AB18, D_00405628, &D_0049AA58);
    }
    return &D_0049AB18;
}
