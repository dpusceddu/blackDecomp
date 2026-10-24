#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00278B48();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00278B48);

s32 func_00278EA0(s32 arg0) {
    return func_00278B48(arg0, 0, M2C_FIELD(arg0, s32 *, 0x30));
}
