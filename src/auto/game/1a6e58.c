#include "auto/prelude.h"

extern s32 func_00345AC8(s32);
extern s32 func_001AC8D0(s32, void *);
extern s32 D_0040F50C;

s32 func_001A6E58(void *arg0) {
    s32 var_3;

    var_3 = -1;
    if (M2C_FIELD(arg0, s32 *, 0x58) != 0) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x54), s32 *, 0x9AC) = 0;
        func_00345AC8(M2C_FIELD(arg0, s32 *, 0x58));
        M2C_FIELD(arg0, s32 *, 0x58) = 0;
        func_001AC8D0(D_0040F50C, arg0);
        var_3 = M2C_FIELD(arg0, s32 *, 0xB0);
        M2C_FIELD(arg0, s32 *, 0xB0) = -1;
    }
    return var_3;
}
