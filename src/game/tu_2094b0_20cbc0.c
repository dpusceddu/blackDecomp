#include "ps2/prelude.h"

extern s32 func_00360A50();
extern s32 D_003BE758;
extern s32 D_003BE820;
extern s32 D_003BE804;
extern s32 D_003BE838;
extern s32 D_003BE75C;
extern s32 D_003BE7D0;
extern s32 D_003BE754;
extern s32 D_003BE7EC;

s32 func_0020CBC0(s32 arg0, s32 arg1, s32 arg2) {
    if (func_00360A50(arg2, D_003BE758) != 0) {
        D_003BE820 = arg1;
        D_003BE804 = arg1;
        D_003BE838 = arg1;
    }
    if (func_00360A50(arg2, D_003BE75C) != 0) {
        D_003BE7D0 = arg1;
    }
    if (func_00360A50(arg2, D_003BE754) != 0) {
        D_003BE7EC = arg1;
    }
    return arg1;
}

void func_0020CC58(void) {

}
