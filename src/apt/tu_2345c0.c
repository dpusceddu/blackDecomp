#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_002345C0();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002345C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00234710);

s32 func_00234718(s32 arg0, s32 arg1) {
    return func_002345C0(arg0, arg1, 0);
}

s32 func_00234738(s32 arg0, s32 arg1) {
    return func_002345C0(arg0, arg1, 1);
}
