#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0040EBC0;
extern s32 func_00370188();

s32 * func_00389100(void) {
    if (D_0040EBC0 == 0) {
        func_00370188(&D_0040EBC0, "Q24Kaim7CObject");
    }
    return &D_0040EBC0;
}

f32 func_00389140(void *arg0) {
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f2;

    temp_f1 = M2C_FIELD(arg0, f32 *, 0);
    temp_f2 = M2C_FIELD(arg0, f32 *, 4);
    temp_f0 = M2C_FIELD(arg0, f32 *, 8);
    return (temp_f1 * temp_f1) + (temp_f2 * temp_f2) + (temp_f0 * temp_f0);
}

void func_00389168(void) {

}

s32 func_00389170(void) {
    return 1;
}
