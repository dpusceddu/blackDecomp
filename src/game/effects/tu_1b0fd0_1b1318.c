#include "include_asm.h"
#include "ps2/prelude.h"

void * func_001B1318(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s128 *, 0) = (s128) M2C_FIELD(arg1, s128 *, 0x20);
    M2C_FIELD(arg0, s128 *, 0x10) = (s128) M2C_FIELD(arg1, s128 *, 0x30);
    M2C_FIELD(arg0, s128 *, 0x20) = (s128) M2C_FIELD(arg1, s128 *, 0x40);
    M2C_FIELD(arg0, s128 *, 0x30) = (s128) M2C_FIELD(arg1, s128 *, 0x50);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B1340);
