#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00253E60();
extern s32 func_003608B8();

s32 func_002537B0(s32 arg0) {
    u16 temp_5;

    temp_5 = M2C_FIELD(M2C_FIELD(arg0, u32 *, 0), u16 *, 2);
    func_00253E60(arg0, (s32) temp_5, 0, (s32) temp_5, 1, (s32) temp_5);
    func_003608B8((s32) (M2C_FIELD(arg0, u32 *, 0) + 8));
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00253800);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00253810);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002539A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002539C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00253AC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00253AC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00253B10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00253BE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00253D28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00253D30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00253E58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00253E60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00253FF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002540B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00254120);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00259550);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00259558);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00259848);
