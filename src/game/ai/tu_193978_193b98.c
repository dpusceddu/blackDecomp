#include "include_asm.h"
#include "ps2/prelude.h"

extern void* func_00193B40(void*);

void* func_00193B98(void* action) {
    return (u8*)func_00193B40(action) + 0xC;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_193978_193b98", func_00193BB8);
