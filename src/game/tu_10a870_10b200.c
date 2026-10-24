#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "game/layouts/Recovered_FrontendSaveDialog.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_0010B200(Recovered_FrontendSaveDialog *arg0) {
    s32 var_3;
    u8 *var_2;

    var_3 = 2;
    var_2 = &arg0->field_52B;
    do {
        M2C_FIELD(var_2, s8 *, -3) = 0;
        var_3 -= 1;
        M2C_FIELD(var_2, u8 *, 0) = 0;
        var_2 = (u8 *) (((s8 *) var_2) + 1);
    } while (var_3 >= 0);
    arg0->field_515 = 0;
    arg0->field_C = 8;
    arg0->field_24 = 0;
    return 8;
}
