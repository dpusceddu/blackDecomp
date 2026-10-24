#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00147A98(s32 *, s32, s32, s32, s32, s32, s32);

void func_001479B8(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 temp_25;
    void *temp_11;
    void *temp_11_2;
    void *temp_11_3;
    void *temp_3;
    void *temp_3_2;
    void *temp_4;

    temp_25 = arg1 * 6;
    temp_4 = temp_25 + M2C_FIELD(arg0, s32 *, 0x1A8);
    if ((M2C_FIELD(temp_4, u8 *, 0) == 0) || ((M2C_FIELD(temp_4, u8 *, 1) == 0) && (arg2 != 0))) {
        M2C_FIELD(temp_4, u8 *, 0) = 1U;
        temp_11 = temp_25 + M2C_FIELD(arg0, s32 *, 0x1A8);
        M2C_FIELD(temp_11, u8 *, 3) = (u8) ((M2C_FIELD(temp_11, u8 *, 3) != 0) | (arg4 != 0));
        temp_3 = temp_25 + M2C_FIELD(arg0, s32 *, 0x1A8);
        M2C_FIELD(temp_3, u8 *, 2) = (u8) ((M2C_FIELD(temp_3, u8 *, 2) != 0) | (arg3 != 0));
        temp_11_2 = temp_25 + M2C_FIELD(arg0, s32 *, 0x1A8);
        M2C_FIELD(temp_11_2, u8 *, 1) = (u8) ((M2C_FIELD(temp_11_2, u8 *, 1) != 0) | (arg2 != 0));
        temp_3_2 = temp_25 + M2C_FIELD(arg0, s32 *, 0x1A8);
        M2C_FIELD(temp_3_2, u8 *, 4) = (u8) ((M2C_FIELD(temp_3_2, u8 *, 4) != 0) | (arg5 != 0));
        temp_11_3 = temp_25 + M2C_FIELD(arg0, s32 *, 0x1A8);
        M2C_FIELD(temp_11_3, u8 *, 5) = (u8) ((M2C_FIELD(temp_11_3, u8 *, 5) != 0) | (arg6 != 0));
        func_00147A98(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00147A98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00147B90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00147D28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001480E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001482C8);
