#include "auto/prelude.h"

extern s32 func_00316698();
extern s32 func_003166F8();

s32 func_003165C8(s32 arg0, s32 arg1) {
    func_00316698(arg0);
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) & 0xFFFFFFFD);
    return arg0;
}

s32 func_00316618(s32 arg0, s32 arg1) {
    func_003166F8(arg0);
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) & 0xFFFFFFFE);
    return arg0;
}

s32 func_00316668(s32 arg0) {
    func_003166F8();
    func_00316698(arg0);
    return arg0;
}
