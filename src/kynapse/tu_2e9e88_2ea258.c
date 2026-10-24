#include "include_asm.h"
#include "ps2/prelude.h"

extern f32 func_0029DC18(f32);
extern f32 func_0029DA28(f32);

void func_002EA258(void *arg0, void *arg1) {
    f32 temp_f20;
    f32 temp_f20_2;

    temp_f20 = func_0029DC18(M2C_FIELD(arg0, f32 *, 4) * 0.017453292f);
    M2C_FIELD(arg1, f32 *, 0) = (f32) (temp_f20 * func_0029DA28(M2C_FIELD(arg0, f32 *, 0) * 0.017453292f));
    temp_f20_2 = func_0029DA28(M2C_FIELD(arg0, f32 *, 4) * 0.017453292f);
    M2C_FIELD(arg1, f32 *, 8) = (f32) (temp_f20_2 * func_0029DA28(M2C_FIELD(arg0, f32 *, 0) * 0.017453292f));
    M2C_FIELD(arg1, f32 *, 4) = func_0029DC18(M2C_FIELD(arg0, f32 *, 0) * 0.017453292f);
}
