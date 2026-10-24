#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_001F7A18(void *, u32, s128);
extern void * D_0040F518;

s32 func_001F2C68(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s128 arg4, s32 arg5) {
    func_001F7A18(M2C_FIELD(D_0040F518, void **, 0xC), (u32) arg1, arg4);
    return 1;
}
