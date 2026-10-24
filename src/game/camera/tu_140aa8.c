#include "include_asm.h"
#include "ps2/prelude.h"

void func_00140AA8(void) {

}

void func_00140AB0(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0xFA) = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00140AB8);
