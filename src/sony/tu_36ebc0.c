#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void func_00367C90(); /* Deci2Call */

void func_0036EBC0(s32 arg0, s32 arg1) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s32 *)(sp + 0) = arg0;
    func_00367C90(0x10, sp);
}
