#include "auto/prelude.h"

extern char D_0040C0E0[];
const u32 rodata_0040C0E0[4] __asm__("D_0040C0E0") __attribute__((aligned(8))) = { 0x00000000, 0x003714B0, 0x00000000, 0x00371500 };

void func_00370CE0(void *arg0, s32 arg1, s32 arg2) {
    if (arg0 != NULL) {
        M2C_FIELD(arg0, s32 *, 8) = arg2;
        M2C_FIELD(arg0, s32 *, 0) = arg1;
        M2C_FIELD(arg0, M2C_UNK **, 4) = &D_0040C0E0;
    }
}
