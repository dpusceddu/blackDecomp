#include "auto/prelude.h"

extern s32 func_003778D8();
extern s32 func_00377968();

void func_00377868(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14C) = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x124), s32 *, 0x10) + (func_003778D8() << 5));
}

void func_003778A0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14C) = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x124), s32 *, 0x10) + (func_00377968() << 5));
}
