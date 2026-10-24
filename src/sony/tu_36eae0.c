#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void func_00367C90(); /* Deci2Call */

void func_0036EAE0(s32 arg0, s8 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s32 *)(sp + 0) = arg0;
    *(s32 *)(sp + 4) = (s32) arg1;
    func_00367C90(3, sp);
}

void func_0036EB10(s32 arg0) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s32 *)(sp + 0) = arg0;
    func_00367C90(4, sp);
}
