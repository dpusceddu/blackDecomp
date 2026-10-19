#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "recovered/Recovered_ZeroedBase.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern M2C_UNK D_003EA7C0;

void * func_002E7360(Recovered_ZeroedBase *arg0) {
    u32 *var_3;
    u32 var_5;

    var_5 = 0;
    var_3 = &arg0->field_4;
    arg0->field_0 = (u32) &D_003EA7C0;
    do {
        *var_3 = 0;
        var_5 += 1;
        var_3 = (u32 *) (((s8 *) var_3) + 4);
    } while (var_5 < 8U);
    return arg0;
}
