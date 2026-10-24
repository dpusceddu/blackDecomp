#include "include_asm.h"
#include "ps2/prelude.h"

#include "kynapse/partial/Recovered_Vtable_003EDC38.h"
#include "ps2/recovered_types.h"

s32 func_002F3530(Recovered_Vtable_003EDC38 *arg0, s32 arg1) {
    s32 *temp_3;
    s32 *var_2;
    void *temp_4;

    temp_4 = arg0->field_4;
    if ((u32) arg1 >= (u32) M2C_FIELD(temp_4, u32 *, 0xC)) {
        var_2 = NULL;
    } else {
        temp_3 = (arg1 * 0x14) + M2C_FIELD(temp_4, s32 *, 0x18);
        var_2 = (~*temp_3 == 0) ? NULL : temp_3;
    }
    return (s32) ((void *) (((s8 *) var_2) + 4));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F3570);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F3590);
