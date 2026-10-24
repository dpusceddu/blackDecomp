#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00317C20(M2C_UNK *, void *);
extern M2C_UNK D_00455F30;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003102D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310330);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310338);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310478);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310590);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003105E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003105E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310698);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003106F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310748);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310768);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003107E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310858);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310870);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003108E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003108F0);

void func_00310940(void *arg0) {
    if (!(M2C_FIELD(arg0, s32 *, 0x10) & 1)) {
        func_00317C20(&D_00455F30, arg0);
    }
}
