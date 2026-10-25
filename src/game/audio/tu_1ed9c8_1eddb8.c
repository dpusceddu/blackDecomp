#include "include_asm.h"
#include "ps2/prelude.h"

extern void * D_0040F4D0;
extern s32 func_001EDD80();

void func_001EDDB8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 2;
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) (M2C_FIELD(D_0040F4D0, f32 *, 0x20) + M2C_FIELD(arg0, f32 *, 0x38));
}


void func_001EE150(void) {

}


void func_001EE270(void) {

}


void func_001EE670(void) {

}


void func_001EE850(void *arg0) {
    f32 temp_f1;

    func_001EDD80();
    temp_f1 = M2C_FIELD(arg0, f32 *, 4);
    M2C_FIELD(arg0, f32 *, 8) = temp_f1;
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) (M2C_FIELD(arg0, f32 *, 0x20) / temp_f1);
}
