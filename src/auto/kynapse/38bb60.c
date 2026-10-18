#include "auto/prelude.h"

extern char D_00406010[];
const char rodata_00406010[112] __asm__("D_00406010") __attribute__((aligned(8))) = "Q24Kaim11CAgentClass" "\000\000\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim6CAgentZPFPQ24Kaim6CBrain_PQ24Kaim6CAgent" "\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049B040;
extern s32 func_00389370();
extern s32 func_00370168();
extern M2C_UNK D_0040EBC8;

s32 * func_0038BB60(void) {
    if (D_0049B040 == 0) {
        func_00389370();
        func_00370168(&D_0049B040, D_00406010, &D_0040EBC8);
    }
    return &D_0049B040;
}
