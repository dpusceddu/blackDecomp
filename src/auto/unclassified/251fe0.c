#include "auto/prelude.h"

extern s32 func_00251B38();
extern M2C_UNK D_003E1C40;
extern s32 func_00251D98();
extern M2C_UNK D_003E1B68;

s32 func_00251FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00251B38(arg0, 0x2B, arg1, arg3, 1);
    M2C_FIELD(arg0, s32 *, 0x30) = arg2;
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E1C40;
    return arg0;
}

s32 func_00252030(s32 arg0, s32 arg1, s32 arg2) {
    func_00251D98(arg0, 0x2B, arg1, arg2);
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E1C40;
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) M2C_FIELD(arg1, s32 *, 0x30);
    return arg0;
}

s32 func_00252088(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00251B38(arg0, 0x2C, arg1, arg3, 1);
    M2C_FIELD(arg0, s32 *, 0x30) = arg2;
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E1B68;
    return arg0;
}

s32 func_002520D8(s32 arg0, s32 arg1, s32 arg2) {
    func_00251D98(arg0, 0x2C, arg1, arg2);
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E1B68;
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) M2C_FIELD(arg1, s32 *, 0x30);
    return arg0;
}
