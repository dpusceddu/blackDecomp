#include "include_asm.h"
#include "ps2/prelude.h"

void func_00204FF0(void* arg0, void* manager) {
    M2C_FIELD(arg0, void**, 8) = manager;
    M2C_FIELD(arg0, s8*, 0x12) = 0;
    M2C_FIELD(arg0, s32*, 0) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_204ff0", func_00205000);
