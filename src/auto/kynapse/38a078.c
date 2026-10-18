#include "auto/prelude.h"

extern char D_00404DB8[];
const char rodata_00404DB8[176] __asm__("D_00404DB8") __attribute__((aligned(8))) = "Q24Kaim18CEntityEyePosition" "\000\000\000\000\000" "Q24Kaim7CObject" "\000" "Q24Kaim16CEntityAttribute" "\000\000\000\000\000\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim16CEntityAttributeZPFv_PQ24Kaim16CEntityAttribute" "\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049AA68;
extern s32 func_00389F90();
extern s32 func_00370168();
extern M2C_UNK D_0049AA58;

s32 * func_0038A078(void) {
    if (D_0049AA68 == 0) {
        func_00389F90();
        func_00370168(&D_0049AA68, D_00404DB8, &D_0049AA58);
    }
    return &D_0049AA68;
}
