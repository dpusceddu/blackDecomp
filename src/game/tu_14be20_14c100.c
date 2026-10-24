#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0014C0C8();
extern s32 func_00126098();
extern s32 func_0014C088();

s32 func_0014C100(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    return func_0014C0C8(arg0, arg5);
}

s32 func_0014C120(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    return func_00126098(arg0, arg1, arg2, arg3, arg4, arg5, arg0 + 0xE0);
}

s32 func_0014C140(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_0014C088(arg0, M2C_FIELD(arg3, s32 *, 0x124));
}
