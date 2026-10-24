#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_001EA510(s32);
extern s32 func_001E8120();

void func_001E9640(void *arg0) {
    func_001EA510(M2C_FIELD(arg0, s32 *, 0x174));
}

void func_001E9660(void *arg0) {
    func_001E8120();
    M2C_FIELD(arg0, s32 *, 0x1B8) = 0;
}
