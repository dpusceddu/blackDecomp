#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035B470);

#include "ps2/recovered_types.h"
extern void func_003678A0(); /* WaitSema */
extern s32 D_0047EA00;
extern s32 * func_003680A0(s32 *, s32);
extern s32 D_00480B00;

void * func_0035B540(void) {
    func_003678A0(D_0047EA00);
    func_003680A0(&D_00480B00, (s32) ((void *) (((s8 *) &D_00480B00) + 0x7F)));
    if (M2C_FIELD(&D_00480B00, s32 *, 0) <= 0) {
        M2C_FIELD(&D_00480B00, s32 *, 8) = 0;
    }
    return &D_00480B00;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035B598);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035B5C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035B658);
