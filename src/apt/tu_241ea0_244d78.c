#include "ps2/prelude.h"

extern s32 func_00244CE8(s32 *arg0);
extern s32 func_00244CF8(s32 *);
extern s32 func_00250198(s32, void *, M2C_UNK);
extern s32 D_0043DEE0;

void func_00244D78(s32 *arg0) {
    *arg0 += 1;
}

void func_00244D88(s32 *arg0) {
    *arg0 -= 1;
}

void func_00244D98(void *arg0) {
    s32 *temp_4;

    if (arg0 != NULL) {
        temp_4 = M2C_FIELD(arg0, s32 **, 4);
        if ((temp_4 != NULL) && (func_00244CE8(temp_4) == 0)) {
            func_00244CF8(M2C_FIELD(arg0, s32 **, 4));
        }
        func_00250198(D_0043DEE0, arg0, 0x10);
    }
}
