#include "include_asm.h"
#include "ps2/prelude.h"

void func_00384630(void) {

}

void func_00384638(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
}

void func_00384640(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
}

s32 func_00384648(s32 arg0) {
    return arg0;
}

void func_00384650(f32 *arg0, f32 fparg0) {
    *arg0 = fparg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/inline/linkonce_384630", func_00384658);
