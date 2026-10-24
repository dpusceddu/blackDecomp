#include "ps2/prelude.h"

extern char D_00407A58[];
const char rodata_00407A58[120] __asm__("D_00407A58") __attribute__((aligned(8))) = "Q24Kaim11CPathObject" "\000\000\000\000" "Q24Kaim7CObject" "\000" "Q24Kaimt10CMetaClass2ZQ24Kaim7CEntityZPFPCcPv_PQ24Kaim7CEntity" "\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049BC60;
extern s32 func_0038CB28();
extern s32 func_00370168();
extern M2C_UNK D_0049B4E8;

s32 * func_00391238(void) {
    if (D_0049BC60 == 0) {
        func_0038CB28();
        func_00370168(&D_0049BC60, D_00407A58, &D_0049B4E8);
    }
    return &D_0049BC60;
}
