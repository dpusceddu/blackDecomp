#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "game/layouts/Recovered_Vtable_003E0B90.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001F1C08(void *);

s32 func_001F7B90(Recovered_Vtable_003E0B90 *arg0) {
    s32 var_2;
    void **var_16;

    func_001F1C08(arg0);
    var_16 = &arg0->field_1C;
    var_2 = 1;
    do {
        *var_16 = NULL;
        var_2 -= 1;
        var_16 = (void **) (((s8 *) var_16) + -4);
    } while (var_2 >= 0);
    return var_2;
}
