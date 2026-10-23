#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "recovered/Recovered_Object59D40.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern M2C_UNK D_003EC9F0;
extern void * D_003C9ED4;

void * func_002F1358(Recovered_Object59D40 *arg0) {
    f32 var_f1;
    f32 var_f2;

    arg0->field_54 = 0;
    var_f1 = 0.0f;
    arg0->field_0 = (u32) &D_003EC9F0;
    if (D_003C9ED4 != NULL) {
        var_f1 = M2C_FIELD(D_003C9ED4, f32 *, 0xC);
    }
    var_f2 = 0.0f;
    arg0->field_58 = var_f1 * 100.0f;
    if (D_003C9ED4 != NULL) {
        var_f2 = M2C_FIELD(D_003C9ED4, f32 *, 0xC);
    }
    arg0->field_5C = var_f2 * 20.0f;
    return arg0;
}
