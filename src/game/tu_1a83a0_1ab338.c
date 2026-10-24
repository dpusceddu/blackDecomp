#include "ps2/prelude.h"

extern s32 func_0035CBC0();
extern s32 func_0035C7A4();
extern s32 func_00345F28();

s32 func_001AB338(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, void *arg5) {
    u8 sp[16];
    func_0035CBC0(arg1, arg2);
    func_0035C7A4(arg1, arg3);
    func_0035C7A4(arg1, arg4);
    return func_00345F28(arg1, M2C_FIELD(M2C_FIELD(arg5, void **, 0x330), s32 *, 0x54), sp) == 1;
}
