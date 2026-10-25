#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00310978(M2C_UNK *, s32, s32, s32, s32, s32);
extern M2C_UNK D_004585C8;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31a850", func_0031A850);

void func_0031A9A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00310978(&D_004585C8, arg0, arg1, 0, arg2, arg3);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31a850", func_0031A9D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31a850", func_0031A9E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31a850", func_0031AA20);
