#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * D_003BCAC8;

s32 func_00124A20(s32 arg0, s32 arg1) {
    s32 *var_3;
    s32 var_4;

    var_4 = 1;
    var_3 = (s32 *) (((s8 *) D_003BCAC8) + 4);
loop_1:
    if (*var_3 != arg1) {
        var_4 += 1;
        var_3 = (s32 *) (((s8 *) var_3) + 4);
        if (var_4 >= 0x25) {
            return var_4;
        }
        goto loop_1;
    }
    return var_4;
}
