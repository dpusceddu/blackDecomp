#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_003242B0();
extern s32 func_00367750();
extern s32 func_00367780();

void func_00326858(s32 arg0) {
    func_003242B0(0, 0, 0, 0x4E, 0, func_00367750(), arg0, 0);
    func_00367780();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323ed0_326858", func_003268A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323ed0_326858", func_003268C0);
