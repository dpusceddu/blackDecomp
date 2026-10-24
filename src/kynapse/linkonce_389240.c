#include "ps2/prelude.h"

extern s32 D_0049A908;
extern s32 func_0038BA88();
extern s32 func_00370168();
extern M2C_UNK D_0049A948;

s32 * func_00389240(void) {
    if (D_0049A908 == 0) {
        func_0038BA88();
        func_00370168(&D_0049A908, "Q24Kaim10CFleeAgent", &D_0049A948);
    }
    return &D_0049A908;
}
