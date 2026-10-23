/* Translation unit tu_1ed9c8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern void * D_0040F4D0;
extern s32 func_001EDD80();

void func_001EDDB8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 2;
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) (M2C_FIELD(D_0040F4D0, f32 *, 0x20) + M2C_FIELD(arg0, f32 *, 0x38));
}

/* Assembly between the functions: func_001EDDE0 (184 bytes), func_001EDE98 (536 bytes), func_001EE0B0 (160 bytes) */

void func_001EE150(void) {

}

/* Assembly between the functions: func_001EE158 (280 bytes) */

void func_001EE270(void) {

}

/* Assembly between the functions: func_001EE278 (32 bytes), func_001EE298 (680 bytes), func_001EE540 (160 bytes), func_001EE5E0 (144 bytes) */

void func_001EE670(void) {

}

/* Assembly between the functions: func_001EE678 (472 bytes) */

void func_001EE850(void *arg0) {
    f32 temp_f1;

    func_001EDD80();
    temp_f1 = M2C_FIELD(arg0, f32 *, 4);
    M2C_FIELD(arg0, f32 *, 8) = temp_f1;
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) (M2C_FIELD(arg0, f32 *, 0x20) / temp_f1);
}
