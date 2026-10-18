#include "auto/prelude.h"

extern char D_004064A0[];
const char rodata_004064A0[156] __asm__("D_004064A0") __attribute__((aligned(8))) = "Q24Kaimt10CMetaClass2ZQ24Kaim7CEntityZPFPCcPv_PQ24Kaim7CEntity" "\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim16CEntityAttributeZPFv_PQ24Kaim16CEntityAttribute" "\000\000" "bad_alloc" "\000\000\000";
extern s32 D_0040EBF8;
extern s32 func_00370188();

s32 * func_0038D240(void) {
    if (D_0040EBF8 == 0) {
        func_00370188(&D_0040EBF8, D_004064A0);
    }
    return &D_0040EBF8;
}
