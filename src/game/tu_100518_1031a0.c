#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00107E28(s32);
extern s32 func_0012A0D8(s32);
extern s32 * D_0040F4D0;

s32 func_001031A0(s32 arg0) {
    s32 var_16;
    s32 var_17;

    var_16 = arg0 + 0x21060;
    var_17 = 0;
    do {
        var_17 -= 1;
        func_00107E28(var_16);
        var_16 += 0xC;
    } while (var_17 >= 0);
    return func_0012A0D8((s32) D_0040F4D0);
}
