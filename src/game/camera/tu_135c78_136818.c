#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00136548();

void func_00136818(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x318) = fparg0;
    if (M2C_FIELD(arg0, s32 *, 0xB8) != 0) {
        func_00136548();
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00136848);
