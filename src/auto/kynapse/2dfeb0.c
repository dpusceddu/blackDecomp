#include "auto/prelude.h"

extern s32 func_0038B840();
extern M2C_UNK D_003E6D28;

void * func_002DFEB0(void *arg0, void *arg1, void *arg2) {
    func_0038B840((s32) arg0, (s32) arg1, (s32) arg2, 0, 0, 0);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E6D28;
    return arg0;
}
