#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "recovered/Recovered_Vtable_003E08D8.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

void * func_001D8DF8(Recovered_Vtable_003E08D8 *arg0) {
    s32 var_3;
    u32 *var_2;

    arg0->field_1C = 0;
    var_3 = 1;
    arg0->field_10 = 0;
    var_2 = &arg0->field_18;
    do {
        *var_2 = 0;
        var_3 -= 1;
        var_2 = (u32 *) (((s8 *) var_2) + -4);
    } while (var_3 >= 0);
    arg0->field_4 = 0;
    M2C_FIELD(arg0, f32 *, 0) = 1.0f;
    return var_2;
}
