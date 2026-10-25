#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_Object59D40: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Object59D40 {
    u32 unk_0;
    u8 unk_4[80];
    u32 unk_54;
    f32 unk_58;
    f32 unk_5C;
} Recovered_Object59D40;

#include "ps2/recovered_types.h"
extern M2C_UNK D_003EC9F0;
extern void * D_003C9ED4;

void * func_002F1358(Recovered_Object59D40 *arg0) {
    f32 var_f1;
    f32 var_f2;

    arg0->unk_54 = 0;
    var_f1 = 0.0f;
    arg0->unk_0 = (u32) &D_003EC9F0;
    if (D_003C9ED4 != NULL) {
        var_f1 = M2C_FIELD(D_003C9ED4, f32 *, 0xC);
    }
    var_f2 = 0.0f;
    arg0->unk_58 = var_f1 * 100.0f;
    if (D_003C9ED4 != NULL) {
        var_f2 = M2C_FIELD(D_003C9ED4, f32 *, 0xC);
    }
    arg0->unk_5C = var_f2 * 20.0f;
    return arg0;
}

