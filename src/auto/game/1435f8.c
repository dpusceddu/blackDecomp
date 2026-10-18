#include "auto/prelude.h"

extern s32 func_001D74C8(s32);
extern void * D_0040F510;

s32 func_001435F8(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 8) = arg1;
    M2C_FIELD(arg0, s32 *, 0xC) = arg2;
    M2C_FIELD(arg0, s32 *, 0x10) = func_001D74C8(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0xC));
    M2C_FIELD(arg0, s8 *, 0x31) = 0;
    return 1;
}
