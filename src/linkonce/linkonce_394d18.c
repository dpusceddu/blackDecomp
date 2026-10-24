#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_004090D8[];
const char rodata_004090D8[136] __asm__("D_004090D8") __attribute__((aligned(8))) = "Q24Kaim14CEntityManager" "\000" "Q24Kaim13CBrainService" "\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim13CBrainServiceZPFPQ24Kaim6CBrain_PQ24Kaim13CBrainService" "\000\000";
extern s32 D_0049BEC0;
extern s32 func_0038D390();
extern s32 func_00370168();
extern s32 D_0049B950;

void * func_00394D18(void) {
    if (D_0049BEC0 == 0) {
        func_0038D390();
        func_00370168(&D_0049BEC0, D_004090D8, &D_0049B950);
    }
    return &D_0049BEC0;
}
