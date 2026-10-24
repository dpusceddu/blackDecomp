#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_Object59DB0: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Object59DB0 {
    u32 unk_0;
    u8 unk_4[320];
    u32 unk_144;
    u32 unk_148;
    f32 unk_14C;
    f32 unk_150;
} Recovered_Object59DB0;

#include "ps2/recovered_types.h"
extern M2C_UNK D_003EC9C0;
extern void * D_003C9ED4;

void * func_002F1678(Recovered_Object59DB0 *arg0) {
    f32 var_f0;
    s32 var_3;

    var_3 = 0x13;
    arg0->unk_0 = (u32) &D_003EC9C0;
    do {
        var_3 -= 1;
    } while (var_3 != -1);
    arg0->unk_144 = 0;
    arg0->unk_148 = 0;
    var_f0 = 0.0f;
    arg0->unk_14C = 20.0f;
    if (D_003C9ED4 != NULL) {
        var_f0 = M2C_FIELD(D_003C9ED4, f32 *, 0xC);
    }
    arg0->unk_150 = var_f0 * 20.0f;
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F16E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F18D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F1B58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F1BD8);
