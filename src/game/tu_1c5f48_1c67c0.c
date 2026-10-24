#include "include_asm.h"
#include "ps2/prelude.h"

#include "game/partial/Recovered_BkActorRenderPS2.h"
#include "ps2/recovered_types.h"
extern s32 func_001C6FA0(void *, s32);
extern s32 func_001C5F48(s32);
extern Recovered_BkActorRenderPS2 * D_0040F4C0;

s32 func_001C67C0(s32 arg0, s32 arg1) {
    s32 temp_17;
    s32 var_16;
    s32 var_4;

    var_16 = arg0;
    temp_17 = var_16 + 0x70;
    var_4 = var_16;
    do {
        func_001C6FA0((void *) var_4, arg1);
        var_16 += 0x38;
        var_4 = var_16;
    } while (var_16 < temp_17);
    return func_001C5F48((s32) D_0040F4C0);
}
