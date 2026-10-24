#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00405498[];
const char rodata_00405498[184] __asm__("D_00405498") __attribute__((aligned(8))) = "Q24Kaim23CEntityTorsoOrientation" "\000\000\000\000\000\000\000\000" "Q24Kaim7CObject" "\000" "Q24Kaim16CEntityAttribute" "\000\000\000\000\000\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim16CEntityAttributeZPFv_PQ24Kaim16CEntityAttribute" "\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049AAF8;
extern s32 func_00389F90();
extern s32 func_00370168();
extern M2C_UNK D_0049AA58;

s32 * func_0038A8B0(void) {
    if (D_0049AAF8 == 0) {
        func_00389F90();
        func_00370168(&D_0049AAF8, D_00405498, &D_0049AA58);
    }
    return &D_0049AAF8;
}
