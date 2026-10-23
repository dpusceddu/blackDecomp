#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001AF1B8(void *);

s32 func_001AF6D0(s32 arg0) {
    s32 var_17;
    void *var_16;

    var_16 = arg0 + 0xCA58;
    var_17 = 6;
    do {
        var_17 -= 1;
        func_001AF1B8(var_16);
        var_16 = (void *) (((s8 *) var_16) + 0x18);
    } while (var_17 >= 0);
    M2C_FIELD(arg0, s32 *, 0xCBC8) = 0;
    return arg0 + 0x8000;
}
