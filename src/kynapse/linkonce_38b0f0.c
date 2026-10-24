#include "ps2/prelude.h"

extern s32 D_0049ABA8;
extern s32 * func_0038AFB8();
extern s32 func_00370168();
extern s32 D_0049AB88;

s32 * func_0038B0F0(void) {
    if (D_0049ABA8 == 0) {
        func_0038AFB8();
        func_00370168(&D_0049ABA8, "Q24Kaim12CPointMapper", &D_0049AB88);
    }
    return &D_0049ABA8;
}
