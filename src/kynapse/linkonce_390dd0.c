#include "ps2/prelude.h"

extern s32 D_0049BC10;
extern s32 func_00390E48();
extern s32 func_00370168();
extern M2C_UNK D_0049BC20;

s32 * func_00390DD0(void) {
    if (D_0049BC10 == 0) {
        func_00390E48();
        func_00370168(&D_0049BC10, "Q24Kaim13CGraphWrapper", &D_0049BC20);
    }
    return &D_0049BC10;
}
