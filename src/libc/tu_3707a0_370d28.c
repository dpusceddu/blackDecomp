#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_0040C0B0[];
const u32 rodata_0040C0B0[4] __asm__("D_0040C0B0") __attribute__((aligned(8))) = { 0x00000000, 0x00371360, 0x00000000, 0x003713B0 };

void func_00370D28(void *arg0, s32 arg1) {
    if (arg0 != NULL) {
        M2C_FIELD(arg0, s32 *, 0) = arg1;
        M2C_FIELD(arg0, M2C_UNK **, 4) = &D_0040C0B0;
    }
}
