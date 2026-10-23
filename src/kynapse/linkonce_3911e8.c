#include "auto/prelude.h"

extern s32 D_0049BC50;
extern s32 func_00389100();
extern s32 func_00370168();
extern M2C_UNK D_0040EBC0;

s32 * func_003911E8(void) {
    if (D_0049BC50 == 0) {
        func_00389100();
        func_00370168(&D_0049BC50, "Q34Kaim11CPathObject11CLinkedEdge", &D_0040EBC0);
    }
    return &D_0049BC50;
}
