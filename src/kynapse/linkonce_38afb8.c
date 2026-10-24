#include "ps2/prelude.h"

extern s32 D_0049AB88;
extern s32 * func_0038E6E0();
extern s32 func_00370168();
extern s32 D_0049AB98;

s32 * func_0038AFB8(void) {
    if (D_0049AB88 == 0) {
        func_0038E6E0();
        func_00370168(&D_0049AB88, "Q24Kaim13CWorldService", &D_0049AB98);
    }
    return &D_0049AB88;
}
