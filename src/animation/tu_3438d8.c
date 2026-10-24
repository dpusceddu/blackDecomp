/* Translation unit animation/tu_3438d8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern void * func_00344020();

void func_003438D8(void) {

}

/* Assembly between the functions: func_003438E0 (336 bytes), func_00343A30 (400 bytes) */

void * func_00343BC0(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2) {
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) (M2C_FIELD(arg0, f32 *, 0x10) * fparg0);
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) (M2C_FIELD(arg0, f32 *, 0x14) * fparg1);
    M2C_FIELD(arg0, f32 *, 0x18) = (f32) (M2C_FIELD(arg0, f32 *, 0x18) * fparg2);
    return arg0;
}

void * func_00343BF0(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) -M2C_FIELD(arg0, f32 *, 0x10);
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) -M2C_FIELD(arg0, f32 *, 0x14);
    M2C_FIELD(arg0, f32 *, 0x18) = (f32) -M2C_FIELD(arg0, f32 *, 0x18);
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) -M2C_FIELD(arg0, f32 *, 0xC);
    return arg0;
}

s32 func_00343C28(s32 arg0, s32 arg1) {
    if (arg0 != 0) {
        if (arg1 != 0) {
            func_00344020();
        }
    }
    return arg0;
}
