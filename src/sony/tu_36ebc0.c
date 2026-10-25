#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern void func_00367C90(); /* Deci2Call */

void func_0036EBC0(s32 arg0, s32 arg1) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s32 *)(sp + 0) = arg0;
    func_00367C90(0x10, sp);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36ebc0", func_0036EBE8);
