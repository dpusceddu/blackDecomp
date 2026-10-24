#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_0014D3B8(void *);

s32 func_0014D910(s32 arg0) {
    s32 temp_17;
    s32 var_16;

    var_16 = arg0;
    temp_17 = var_16 + 0xF0;
    do {
        func_0014D3B8((void *) var_16);
        var_16 += 0x18;
    } while (var_16 < temp_17);
    return 1;
}

s32 func_0014D958(s32 arg0) {
    s32 temp_17;
    s32 temp_2;
    s32 var_16;

    var_16 = arg0;
    temp_17 = var_16 + 0xF0;
    do {
        func_0014D3B8((void *) var_16);
        var_16 += 0x18;
        temp_2 = var_16 < temp_17;
    } while (temp_2 != 0);
    return temp_2;
}
