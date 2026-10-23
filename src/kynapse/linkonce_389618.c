#include "auto/prelude.h"

extern char D_00404540[];
const char rodata_00404540[112] __asm__("D_00404540") __attribute__((aligned(8))) = "Q24Kaim13CPathWayAgent" "\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim6CAgentZPFPQ24Kaim6CBrain_PQ24Kaim6CAgent" "\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049A988;
extern s32 func_0038BA88();
extern s32 func_00370168();
extern M2C_UNK D_0049A948;

s32 * func_00389618(void) {
    if (D_0049A988 == 0) {
        func_0038BA88();
        func_00370168(&D_0049A988, D_00404540, &D_0049A948);
    }
    return &D_0049A988;
}
