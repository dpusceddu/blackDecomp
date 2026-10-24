#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 D_003C1664;
extern M2C_UNK * func_0036D518();
extern s32 func_0036A460();
extern s32 func_002A4598();
extern s32 func_0036D568();
extern s32 D_003C1688;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A4410);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A44F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A4598);

s32 func_002A45F0(void) {
    M2C_UNK *temp_16;

    D_003C1664 = 1;
    temp_16 = func_0036D518();
    func_0036A460(0x80000012, func_002A4598, 0);
    if (temp_16 != NULL) {
        func_0036D568();
    }
    D_003C1664 = 0;
    D_003C1688 = 1;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A4668);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A4678);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A46E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A4840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A4B28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A4D40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A4F60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5030);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5038);
