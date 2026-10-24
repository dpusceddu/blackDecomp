#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00272488);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00272580);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00272608);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00272610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002726C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002726D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00272730);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00272788);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002728C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002728D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00272960);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00272A58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00272A60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00272AA8);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00272B78(void *);

s32 func_00272AF8(void *arg0, s32 arg1, s32 arg2, u32 arg3, f32 fparg0) {
    M2C_FIELD(arg0, s32 *, 0x34) = arg1;
    M2C_FIELD(arg0, s32 *, 0x38) = arg2;
    M2C_FIELD(arg0, u32 *, 0x40) = arg3;
    M2C_FIELD(arg0, f32 *, 0x20) = fparg0;
    M2C_FIELD(arg0, f32 *, 0x24) = 300.0f;
    M2C_FIELD(arg0, f32 *, 0x28) = 150.0f;
    M2C_FIELD(arg0, f32 *, 0x2C) = 75.0f;
    M2C_FIELD(arg0, f32 *, 0x30) = 10.0f;
    return func_00272B78(arg0);
}
