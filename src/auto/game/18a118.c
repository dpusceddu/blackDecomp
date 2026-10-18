#include "auto/prelude.h"

extern void * D_0040F4D0;
extern s128 func_00189070();
extern s32 func_0018D768();
extern void func_0018A1C0();
extern void func_0018A238();
extern s32 func_00189C10();

void func_0018A118(void *arg0, void *arg1) {
    if (M2C_FIELD(arg1, s32 *, 0) != -1) {
        if (M2C_FIELD(arg1, u8 *, 6) != 0) {
            M2C_FIELD(arg1, f32 *, 0x10) = (f32) M2C_FIELD(D_0040F4D0, f32 *, 0x20);
            M2C_FIELD(arg1, s128 *, 0x20) = func_00189070();
            M2C_FIELD(arg1, s8 *, 5) = 1;
        }
        if (func_0018D768(M2C_FIELD(arg0, s32 *, 0x130) + 0xD10, M2C_FIELD(arg1, s32 *, 0)) != 0) {
            M2C_FIELD(arg1, f32 *, 0x1C) = (f32) M2C_FIELD(D_0040F4D0, f32 *, 0x20);
        }
        func_0018A1C0(arg0, arg1);
        func_0018A238(arg0, arg1);
    }
    func_00189C10(arg0, arg1);
}
