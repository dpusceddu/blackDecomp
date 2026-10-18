#include "auto/prelude.h"

extern s32 func_00160E10(s32, s32);
extern void * D_0040F0E0;

void func_002019A0(void *arg0, s32 arg1) {
    if ((arg1 == 0) || (func_00160E10(arg1, M2C_FIELD(D_0040F0E0, s32 *, 0x2014C)) != 0)) {
        M2C_FIELD(arg0, s32 *, 0xD8) = 0;
        M2C_FIELD(arg0, s8 *, 0x108) = 1;
    }
}
