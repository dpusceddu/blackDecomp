#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern u8 D_0040E060;
extern M2C_UNK D_00403E98;
extern M2C_UNK D_00403E88;
extern s128 func_002C8CE0(void *, s32, void *, void *);
extern s128 func_002C8E48(void *, s32, void *, void *, void *);

s32 func_002CB248(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_UNK *var_4;

    if (D_0040E060 & 1) {
        var_4 = &D_00403E98;
    } else {
        var_4 = &D_00403E88;
    }
    func_002C8CE0(var_4, 0, arg0 + (arg2 << 6), arg0 + (arg3 << 6));
    return 1;
}

s32 func_002CB2A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    M2C_UNK *var_4;

    if (D_0040E060 & 1) {
        var_4 = &D_00403E98;
    } else {
        var_4 = &D_00403E88;
    }
    func_002C8E48(var_4, 0, arg0 + (arg2 << 6), arg0 + (arg3 << 6), arg0 + (arg4 << 6));
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2c8728_2cb248", func_002CB300);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2c8728_2cb248", func_002CB370);
