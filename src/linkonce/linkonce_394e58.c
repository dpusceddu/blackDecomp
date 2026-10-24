#include "ps2/prelude.h"

#include "types_ghidra.h"
extern M2C_UNK D_003F15D0;
extern s32 D_003F15B4;
extern s32 func_00107D48();

s32 func_00394E58(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003F15D0;
    M2C_FIELD(arg0, u32 *, 0) = &D_003F15D0;
    D_003F15B4 = 0;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}
