#include "auto/prelude.h"

extern f32 func_00348A38();
extern f32 * func_003500E0();

void func_0034E758(void *arg0, void *arg1, s32 *arg2) {
    f32 temp_f20;
    void *temp_16;

    temp_16 = M2C_FIELD(arg1, void **, 8);
    temp_f20 = func_00348A38(M2C_FIELD(temp_16, s32 *, 0), arg0);
    *func_003500E0(arg2, M2C_FIELD(temp_16, s32 *, 0xC)) = (temp_f20 - M2C_FIELD(temp_16, f32 *, 4)) / M2C_FIELD(temp_16, f32 *, 8);
}

void func_0034E7C0(void *arg0, void *arg1, s32 *arg2) {
    f32 temp_f20;
    void *temp_16;

    temp_16 = M2C_FIELD(arg1, void **, 8);
    temp_f20 = func_00348A38(M2C_FIELD(temp_16, s32 *, 0), arg0);
    *func_003500E0(arg2, M2C_FIELD(temp_16, s32 *, 0xC)) = (temp_f20 - M2C_FIELD(temp_16, f32 *, 4)) / M2C_FIELD(temp_16, f32 *, 8);
}
