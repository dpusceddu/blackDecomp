#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 (*D_003C0E34)();

s32 func_00292140(void) {
    return D_003C0E34() + 4;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00292168);

s16 func_00292440(void *arg0) {
    return M2C_FIELD(arg0, s16 *, 6);
}

s16 func_00292448(void *arg0) {
    return M2C_FIELD(arg0, s16 *, 4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00292450);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00292528);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00292670);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002926F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00292778);

void func_00292808(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00292810);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00292B40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00292D20);
