#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "kynapse/layouts/Recovered_Object59DB0.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern M2C_UNK D_003EC9C0;
extern void * D_003C9ED4;

void * func_002F1678(Recovered_Object59DB0 *arg0) {
    f32 var_f0;
    s32 var_3;

    var_3 = 0x13;
    arg0->field_0 = (u32) &D_003EC9C0;
    do {
        var_3 -= 1;
    } while (var_3 != -1);
    arg0->field_144 = 0;
    arg0->field_148 = 0;
    var_f0 = 0.0f;
    arg0->field_14C = 20.0f;
    if (D_003C9ED4 != NULL) {
        var_f0 = M2C_FIELD(D_003C9ED4, f32 *, 0xC);
    }
    arg0->field_150 = var_f0 * 20.0f;
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F16E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F18D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F1B58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F1BD8);
