#include "auto/prelude.h"

extern s32 func_001EDD80();

void func_001EE850(void *arg0) {
    f32 temp_f1;

    func_001EDD80();
    temp_f1 = M2C_FIELD(arg0, f32 *, 4);
    M2C_FIELD(arg0, f32 *, 8) = temp_f1;
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) (M2C_FIELD(arg0, f32 *, 0x20) / temp_f1);
}
