#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 * func_00107CF8(void *);
extern s32 * func_00121C08(s32 *);

s32 * func_00121DE8(void *arg0) {
    s32 *temp_2;
    s32 *temp_2_2;

    temp_2_2 = func_00107CF8((void *)0x50);
    M2C_FIELD(arg0, s32 **, 0) = temp_2_2;
    temp_2 = func_00121C08(temp_2_2);
    M2C_FIELD(arg0, s8 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s16 *, 0xE) = 0;
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00121E28);
