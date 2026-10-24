#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_003492F0();
extern s32 func_00349288();

void func_001A7188(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x83) = 0;
    M2C_FIELD(arg0, s32 *, 0x9C) = 0;
    if (M2C_FIELD(arg0, s32 *, 0x94) != 0) {
        M2C_FIELD(arg0, s8 *, 0x69) = 0;
        M2C_FIELD(arg0, s8 *, 0xB5) = 1;
        M2C_FIELD(arg0, s32 *, 0x94) = 0;
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x39C) == 0x26) {
            func_003492F0(M2C_FIELD(arg0, s32 *, 0x54), arg0);
            return;
        }
        func_00349288(M2C_FIELD(arg0, s32 *, 0x54), arg0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A71F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A71F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A72B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A73F0);
