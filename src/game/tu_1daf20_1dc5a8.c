#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "recovered/Recovered_Vtable_003E26B8.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_002810A0(Recovered_Vtable_003E26B8 *);

s32 func_001DC5A8(void *arg0) {
    Recovered_Vtable_003E26B8 *var_17;
    f32 *var_16;
    s32 temp_v0;
    s32 var_18;

    var_16 = (f32 *) (((s8 *) arg0) + 0x68);
    var_17 = (Recovered_Vtable_003E26B8 *) (((s8 *) arg0) + 0x58);
    var_18 = 0;
    do {
        var_18 -= 1;
        temp_v0 = func_002810A0(var_17);
        var_17 = (Recovered_Vtable_003E26B8 *) (((s8 *) var_17) + 0x14);
        *var_16 = -1.0f;
        var_16 = (f32 *) (((s8 *) var_16) + 0x14);
    } while (var_18 >= 0);
    return temp_v0;
}
