#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_Vtable_003E08D8: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Vtable_003E08D8 {
    u8 unk_0[4];
    s32 unk_4;
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    s32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
    u32 unk_2C;
    u32 unk_30;
    u32 unk_34;
    u32 unk_38;
    u32 unk_3C;
} Recovered_Vtable_003E08D8;

#include "ps2/recovered_types.h"

void * func_001D8DF8(Recovered_Vtable_003E08D8 *arg0) {
    s32 var_3;
    u32 *var_2;

    arg0->unk_1C = 0;
    var_3 = 1;
    arg0->unk_10 = 0;
    var_2 = &arg0->unk_18;
    do {
        *var_2 = 0;
        var_3 -= 1;
        var_2 = (u32 *) (((s8 *) var_2) + -4);
    } while (var_3 >= 0);
    arg0->unk_4 = 0;
    M2C_FIELD(arg0, f32 *, 0) = 1.0f;
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8E38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8F38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8FD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D9100);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D91F0);
