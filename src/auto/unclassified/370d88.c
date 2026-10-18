#include "auto/prelude.h"

extern char D_0040C080[];
const u32 rodata_0040C080[4] __asm__("D_0040C080") __attribute__((aligned(8))) = { 0x00000000, 0x00371210, 0x00000000, 0x00371260 };

void func_00370D88(void *arg0, s32 arg1) {
    if (arg0 != NULL) {
        M2C_FIELD(arg0, s32 *, 0) = arg1;
        M2C_FIELD(arg0, M2C_UNK **, 4) = &D_0040C080;
    }
}
