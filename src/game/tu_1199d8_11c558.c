#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_0014BA58();

s32 func_0011C558(void *arg0) {
    func_0014BA58((void *) (((s8 *) arg0) + 0x30));
    M2C_FIELD(arg0, s8 *, 0x15D) = 0;
    M2C_FIELD(arg0, s8 *, 0x15C) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0x150) = 0;
    M2C_FIELD(arg0, s32 *, 0x154) = 0;
    M2C_FIELD(arg0, s32 *, 0x158) = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0011C5A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0011C5A8);
