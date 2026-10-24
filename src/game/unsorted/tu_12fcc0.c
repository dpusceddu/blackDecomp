#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 * func_00165AE0(s32 *);
extern s32 func_00382348(void *, s32);
extern M2C_UNK D_00414D58;

s32 func_0012FCC0(s32 *arg0, s32 *arg1, s32 arg2) {
    s32 temp_v0;

    func_00165AE0(arg0);
    temp_v0 = func_00382348(&D_00414D58, 0x02B9D6F8);
    M2C_FIELD(arg0, s8 *, 0x59) = 0;
    M2C_FIELD(arg0, s8 *, 0x58) = 0;
    M2C_FIELD(arg0, s32 *, 0x50) = 0;
    return temp_v0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012FD08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012FD20);
