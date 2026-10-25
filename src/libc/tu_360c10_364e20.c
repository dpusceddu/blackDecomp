#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_0040B4A0[];
const u32 rodata_0040B4A0[12] __asm__("D_0040B4A0") __attribute__((aligned(8))) = { 0x0040B4D8, 0x0040B4D0, 0x0040B4D0, 0x0040B4D0, 0x0040B4D0, 0x0040B4D0, 0x0040B4D0, 0x0040B4D0, 0x0040B4D0, 0x0040B4D0, 0x7F7F7F7F, 0x7F7F7F7F };

M2C_UNK * func_00364E20(void) {
    return &D_0040B4A0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/libc/tu_360c10_364e20", func_00364E30);
