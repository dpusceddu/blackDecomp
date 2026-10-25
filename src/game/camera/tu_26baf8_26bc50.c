#include "include_asm.h"
#include "ps2/prelude.h"

void func_0026BC50(void *arg0, f32 fparg0) {
    if (fparg0 < 0.0f) {
        M2C_FIELD(arg0, f32 *, 0xCC) = (f32) -fparg0;
        return;
    }
    M2C_FIELD(arg0, f32 *, 0xCC) = fparg0;
}

s32 func_0026BC80(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xEC);
}

#include "ps2/recovered_types.h"

s32 func_0026BC88(void *arg0, f32 fparg0) {
    s32 var_3;

    var_3 = 0;
    if ((fparg0 < 1.0f) && (fparg0 >= 0.0f)) {
        var_3 = 1;
    }
    if ((M2C_FIELD(arg0, u8 *, 0xC) == 0) || (var_3 == 0)) {
        return 0;
    }
    M2C_FIELD(arg0, s8 *, 0x47) = (s8) (s32) (fparg0 * 255.0f);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0026BD28);

void func_0026BE68(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0x4A) = (s8) (arg1 ^ 1);
}
