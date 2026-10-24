#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_003230C0(void *, void *, s32, void *);
extern s32 func_00323090(void *, void *, s32, void *);

s32 func_00322F20(void *arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s32 *)(sp + 0) = arg3;
    func_003230C0(arg2, M2C_FIELD(arg2, void **, 0x40), 1, sp);
    *(s32 *)(sp + 0) = arg1;
    return func_00323090(arg0, M2C_FIELD(arg0, void **, 0x40), 1, sp);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322F80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322FA8);
