#include "auto/prelude.h"

extern u16 D_003BFAF8;
extern s32 func_00253FF0();

s32 func_003872A8(s32 *arg0) {
    return *arg0 == (s32) &D_003BFAF8;
}

u16 ** func_003872C0(u16 **arg0) {
    *arg0 = &D_003BFAF8;
    D_003BFAF8 += 1;
    return arg0;
}

s32 func_003872E0(s32 arg0) {
    func_00253FF0();
    return arg0;
}

u16 ** func_00387308(u16 **arg0, u16 **arg1) {
    u16 *temp_6;

    temp_6 = *arg1;
    *arg0 = temp_6;
    *temp_6 += 1;
    return arg0;
}
