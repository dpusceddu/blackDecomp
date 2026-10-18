#include "auto/prelude.h"

extern void * D_003BFAEC;
extern void * func_00250058(s32, s32);
extern s32 D_0043DEE0;

void func_00252A98(void *arg0) {
    M2C_FIELD(arg0, void **, 8) = (void *) D_003BFAEC;
    D_003BFAEC = arg0;
}

void func_00252AB0(void *arg0) {
    M2C_FIELD(arg0, void **, 8) = (void *) D_003BFAEC;
    D_003BFAEC = arg0;
}

void * func_00252AC8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, void **, 8) = func_00250058(D_0043DEE0, arg1 * 4);
    return arg0;
}
