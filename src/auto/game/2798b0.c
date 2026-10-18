#include "auto/prelude.h"

extern s32 func_002797A0();
extern s32 func_00279700();
extern s32 func_00279390();

s32 func_002798B0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;

    if (M2C_FIELD(arg0, s32 *, 0x44) < 0) {
        func_002797A0(arg0);
    }
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) (M2C_FIELD(arg0, s32 *, 0x40) + 1);
    func_00279700(arg0, 1);
    func_00279390(arg0, arg1, arg2);
    temp_2 = M2C_FIELD(arg0, s32 *, 0x44) + 1;
    M2C_FIELD(arg0, s32 *, 0x44) = temp_2;
    return temp_2;
}
