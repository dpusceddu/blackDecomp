#include "auto/prelude.h"

extern char D_00404680[];
const char rodata_00404680[112] __asm__("D_00404680") __attribute__((aligned(8))) = "Q24Kaim13CShooterAgent" "\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim6CAgentZPFPQ24Kaim6CBrain_PQ24Kaim6CAgent" "\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049A9A8;
extern s32 func_0038BA88();
extern s32 func_00370168();
extern M2C_UNK D_0049A948;

s32 * func_00389720(void) {
    if (D_0049A9A8 == 0) {
        func_0038BA88();
        func_00370168(&D_0049A9A8, D_00404680, &D_0049A948);
    }
    return &D_0049A9A8;
}
