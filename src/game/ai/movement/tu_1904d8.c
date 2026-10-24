#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0018E488();
extern s32 func_0018D698(s32, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001904D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190580);

void func_00190730(void *arg0) {
    func_0018E488();
    func_0018D698(M2C_FIELD(arg0, s32 *, 4) + 0xD10, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190768);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001907E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001908A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190958);
