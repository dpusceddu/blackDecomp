#include "auto/prelude.h"

extern void * D_0040F4D0;
extern s32 func_0012A7C0(void *);
extern s32 func_0012AE58(void *);

void func_00175F10(void *arg0, s32 arg1, s8 arg2) {
    M2C_FIELD(arg0, s8 *, 1) = arg2;
    M2C_FIELD(arg0, s8 *, 0) = 1;
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, f32 *, 8) = (f32) M2C_FIELD(D_0040F4D0, f32 *, 0x20);
}

void func_00175F38(void) {

}

s32 func_00175F40(void) {
    return 1;
}

s32 func_00175F48(void) {
    return 1;
}

s32 func_00175F50(void) {
    return func_0012A7C0(D_0040F4D0) != 0;
}

s32 func_00175F78(void) {
    return func_0012AE58(D_0040F4D0) != 0;
}
