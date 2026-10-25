#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00310978(M2C_UNK *, s32, s32, s32, s32, s32);
extern M2C_UNK D_00458640;

void func_0031B540(s32 arg0, s32 arg1, s32 arg2) {
    func_00310978(&D_00458640, 0, arg0, 0, arg1, arg2);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31aee0_31b540", func_0031B578);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31aee0_31b540", func_0031B5B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31aee0_31b540", func_0031B670);
