#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s128 func_002688E0(f32, f32, f32);
extern u8 func_00268A50(s32);
extern u8 func_00268A78(s32);
extern u8 func_00268AA0(s32);

s32 func_00279700(void *arg0, s32 arg1) {
    f32 var_f12;

    var_f12 = (f32) M2C_FIELD(arg0, s32 *, 0x40) + 1.0f;
    if (arg1 != 0) {
        var_f12 += 0.2f;
    }
    func_002688E0(var_f12, 0.1f, 100.0f);
    func_00268A50(M2C_FIELD(arg0, s32 *, 0x44) > 0);
    func_00268A78(arg1);
    return func_00268AA0(arg1 ^ 1);
}
