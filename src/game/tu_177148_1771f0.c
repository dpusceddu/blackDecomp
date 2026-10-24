#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001777D0(void *);

s32 func_001771F0(void *arg0) {
    s32 var_2;
    void *var_16;

    func_001777D0(arg0);
    var_16 = (void *) (((s8 *) arg0) + 0x980);
    var_2 = 4;
    do {
        M2C_FIELD(var_16, s32 *, -4) = 0;
        var_2 -= 1;
        M2C_FIELD(var_16, s32 *, 0) = 0;
        var_16 = (void *) (((s8 *) var_16) + 8);
    } while (var_2 >= 0);
    return var_2;
}
