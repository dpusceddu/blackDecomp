#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00177350();
extern void func_00177780(void *arg0);

void func_001771A8(void *arg0) {
    func_00177350();
    M2C_FIELD(arg0, s32 *, 0x978) = (s32) (M2C_FIELD(arg0, s32 *, 0x978) + 1);
    func_00177780(arg0);
}
