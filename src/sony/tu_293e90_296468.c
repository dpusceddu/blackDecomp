#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 * func_00294BF8(void *, void *);
extern s32 * func_002962F0(s32 *);

s32 * func_00296468(s32 *arg0, s32 *arg1) {
    u8 sp[8] __attribute__((aligned(16)));
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x868);
    if ((temp_3 != NULL) && (arg0 != NULL) && (M2C_FIELD(arg0, s32 *, 0xC) != 0)) {
        *(s32 * *)(sp + 4) = arg1;
        *(s32 *)(sp + 0) = 0;
        return func_00294BF8(temp_3, sp);
    }
    return func_002962F0(arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002964C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00296500);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00296688);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00296D90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00296FE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00297468);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00297688);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002978C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00297BF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298020);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002981C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298718);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298890);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002989F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298B78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298C60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298CF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298D88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298DC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298DC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298E88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298F78);
