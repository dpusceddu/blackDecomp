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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298DC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298E88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298F78);
