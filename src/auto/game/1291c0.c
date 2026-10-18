#include "auto/prelude.h"

extern s32 func_0014DD98();
extern s32 func_0014DE58();
extern s32 func_0014DF68();

void * func_001291C0(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4) {
    return func_0014DD98(arg0 + (((s32) arg1 * 8) + 0x5ABC), arg1, arg2, arg3, arg4);
}

void * func_001291E8(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5) {
    return func_0014DE58(arg0 + (((s32) arg1 * 8) + 0x5ABC), arg1, arg2, arg3, arg4, M2C_FIELD(arg2, void **, 0x38), M2C_FIELD(arg2, void **, 0x40), arg5);
}

void * func_00129218(void *arg0, void *arg1, void *arg2) {
    return func_0014DF68(arg0 + (((s32) arg1 * 8) + 0x5ABC), arg2);
}
