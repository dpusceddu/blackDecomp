#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00325AD0(s32);

void func_00285AA8(void *arg0) {
    func_00325AD0(M2C_FIELD(arg0, s32 *, 0xCBA8));
}
