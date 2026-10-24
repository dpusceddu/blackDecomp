#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "game/layouts/Recovered_Vtable_003E26E8.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_00284BB0(Recovered_Vtable_003E26E8 *arg0, f32 fparg0) {
    s32 temp_f0;

    temp_f0 = (s32) (fparg0 * 255.0f);
    M2C_FIELD(arg0->field_34, s8 *, 0x84) = (s8) temp_f0;
    return temp_f0;
}

s32 func_00284BD0(Recovered_Vtable_003E26E8 *arg0, f32 fparg0) {
    s32 temp_f0;

    temp_f0 = (s32) (fparg0 * 255.0f);
    M2C_FIELD(arg0->field_34, s8 *, 0x87) = (s8) temp_f0;
    return temp_f0;
}
