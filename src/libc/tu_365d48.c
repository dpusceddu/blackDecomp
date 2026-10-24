#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_00482DA8;
extern s32 func_00367F20();
extern s32 func_00367FE0(s32, s32);
extern s32 func_00367F28(s32, s32, s32);
extern s32 func_00367EA8(s32, s32, s32);
extern s32 func_00367F30(s32);
extern s32 func_00367E28(s32, s32, s32);

s32 func_00365D48(s32 *arg0, s32 arg1) {
    s32 temp_2;

    D_00482DA8 = 0;
    temp_2 = func_00367F20(arg1);
    if ((temp_2 == -1) && (D_00482DA8 != 0)) {
        *arg0 = D_00482DA8;
    }
    return temp_2;
}

s32 func_00365DA0(s32 *arg0, s32 arg1, s32 arg2) {
    s32 temp_2;

    D_00482DA8 = 0;
    temp_2 = func_00367FE0(arg1, arg2);
    if ((temp_2 == -1) && (D_00482DA8 != 0)) {
        *arg0 = D_00482DA8;
    }
    return temp_2;
}

s32 func_00365E00(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_2;

    D_00482DA8 = 0;
    temp_2 = func_00367F28(arg1, arg2, arg3);
    if ((temp_2 == -1) && (D_00482DA8 != 0)) {
        *arg0 = D_00482DA8;
    }
    return temp_2;
}

s32 func_00365E60(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_2;

    D_00482DA8 = 0;
    temp_2 = func_00367EA8(arg1, arg2, arg3);
    if ((temp_2 == -1) && (D_00482DA8 != 0)) {
        *arg0 = D_00482DA8;
    }
    return temp_2;
}

s32 func_00365EC0(s32 *arg0, s32 arg1) {
    s32 temp_2;

    D_00482DA8 = 0;
    temp_2 = func_00367F30(arg1);
    if ((temp_2 == 0xFFFFFFFF) && (D_00482DA8 != 0)) {
        *arg0 = D_00482DA8;
    }
    return temp_2;
}

s32 func_00365F20(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_2;

    D_00482DA8 = 0;
    temp_2 = func_00367E28(arg1, arg2, arg3);
    if ((temp_2 == -1) && (D_00482DA8 != 0)) {
        *arg0 = D_00482DA8;
    }
    return temp_2;
}
