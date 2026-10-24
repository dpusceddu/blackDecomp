#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00179258();
extern s32 D_0040F4D4;
extern s128 * func_00178D30();
extern s32 func_00178E60();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00188BF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00188C38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00188D08);

s32 func_00188F10(void *arg0) {
    return ~M2C_FIELD(arg0, s32 *, 0x120) != 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00188F20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00188F58);

s32 func_00188F80(s32 arg0) {
    return func_00179258(D_0040F4D4 + 0xFA8, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x120) * 0x60) + arg0), s32 *, 0));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00188FB8);

s32 func_00189048(s32 arg0) {
    return func_00189070(arg0, (M2C_FIELD(arg0, s32 *, 0x120) * 0x60) + arg0);
}

s128 func_00189070(s32 arg0, s32 *arg1) {
    return *func_00178D30(func_00179258(D_0040F4D4 + 0xFA8, *arg1));
}

s32 func_001890A8(s32 arg0) {
    return func_00189178(arg0, (M2C_FIELD(arg0, s32 *, 0x120) * 0x60) + arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001890D0);

void func_00189178(s32 arg0, s32 *arg1) {
    func_00178E60(func_00179258(D_0040F4D4 + 0xFA8, *arg1));
}
