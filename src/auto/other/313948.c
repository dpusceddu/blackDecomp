#include "auto/prelude.h"

extern s32 func_003143D8();
extern s32 func_00313F50();
extern s32 func_00313F90();

s32 func_00313948(s32 arg0) {
    return func_003143D8(arg0, (s32) func_00313F50, M2C_FIELD(arg0, s32 *, 0x28));
}

s32 func_00313970(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_003143D8(arg0, (s32) func_00313F90, M2C_FIELD(arg0, s32 *, 0x28));
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    return temp_v0;
}
