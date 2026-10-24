#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0027F9C0(void *, M2C_UNK);
extern void * D_0040F4D0;
extern void func_00118090(void *arg0, s32);

void func_00116F08(void *arg0, s32 arg1) {
    func_0027F9C0(D_0040F4D0, 1);
    M2C_FIELD(arg0, s8 *, 0x20) = 0;
    func_00118090(arg0, arg1);
}

void func_00116F58(void) {

}

void func_00116F60(void) {

}
