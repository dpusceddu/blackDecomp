#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"

s32 func_0030E728(void *arg0, s32 arg1) {
    switch (arg1) {
    case 0x1:
        return (s32) (arg0 + 0xC);
    case 0x2:
        return (s32) (arg0 + 0x10);
    case 0x4:
        return (s32) (arg0 + 0x14);
    case 0x20:
        return (s32) (arg0 + 0x18);
    case 0x8:
        return (s32) (arg0 + 0x1C);
    case 0x10:
        return (s32) (arg0 + 0x20);
    case 0x40:
        return (s32) (arg0 + 0x24);
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E798);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E8D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E988);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E9A8);
