#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00140AD0(void *);

s32 func_0011C878(s32 arg0) {
    s32 temp_v0;
    s32 var_17;
    void *var_16;

    var_16 = arg0 + 0x20;
    var_17 = 7;
    do {
        var_17 -= 1;
        temp_v0 = func_00140AD0(var_16);
        var_16 = (void *) (((s8 *) var_16) + 0x4F0);
    } while (var_17 >= 0);
    return temp_v0;
}
