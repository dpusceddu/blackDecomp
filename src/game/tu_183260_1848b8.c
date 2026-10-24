#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00175F50();
extern void * D_0040F4D4;

s32 func_001848B8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001848C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001849D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00184B40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00184D10);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00184DE0(s32 *);

void func_00184D78(s32 *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, f32 *, 8) = 3.4028235e38f;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    if (M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s32 *, 0), void **, 0x7C), s32 *, 0x3A4) == 1) {
        func_00184DE0(arg0);
    }
    M2C_FIELD((void *) M2C_FIELD(arg0, s32 *, 0), s8 *, 0x284) = 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00184DE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001851C8);

s32 func_00185318(s32 arg0, s32 arg1, s32 arg2) {
    return func_00175F50((s32) (D_0040F4D4 + 0xFA0), arg1, arg2, 0x221, M2C_FIELD(M2C_FIELD(arg0, u32 *, 0), s32 *, 0x7C), 1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00185350);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00185438);
