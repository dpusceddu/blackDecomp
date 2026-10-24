#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_001EABA0(s32 *);

s32 func_001EA898(s32 arg0) {
    s32 temp_17;
    s32 var_16;

    var_16 = arg0;
    temp_17 = var_16 + 0x260;
    do {
        func_001EABA0((s32 *) var_16);
        var_16 += 0x4C;
    } while (var_16 < temp_17);
    return 1;
}
