#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern M2C_UNK D_003DCCA0;
extern s32 func_00107D48();

s32 func_00383840(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003DCCA0;
    M2C_FIELD(arg0, u32 *, 0) = &D_003DCCA0;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00383870);
