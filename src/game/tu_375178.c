#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00375178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003753E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00375590);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003761B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00376358);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00376488);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00376BE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00376DE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00376F70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003772B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00377628);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00377BE0();
extern s32 func_00377C28(void *);

s32 func_003777E0(void *arg0) {
    M2C_FIELD(arg0, s32 (**)(), 0) = func_00377BE0;
    M2C_FIELD(arg0, s32 (**)(void *), 4) = func_00377C28;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
    M2C_FIELD(arg0, s32 *, 0x48) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x34) = 0;
    return (s32) func_00377BE0;
}
