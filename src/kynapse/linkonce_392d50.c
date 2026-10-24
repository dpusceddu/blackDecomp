#include "ps2/prelude.h"

extern s32 D_0049BD10;
extern s32 func_00390060();
extern s32 func_00370168();
extern M2C_UNK D_0049BB20;

s32 * func_00392D50(void) {
    if (D_0049BD10 == 0) {
        func_00390060();
        func_00370168(&D_0049BD10, "Q24Kaim15CAccessWaysData", &D_0049BB20);
    }
    return &D_0049BD10;
}
