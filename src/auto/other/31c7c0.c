#include "auto/prelude.h"

extern void * func_00312C48();

void func_0031C7C0(void *arg0) {
    M2C_FIELD(arg0, void **, 0x50) = func_00312C48(M2C_FIELD(arg0, s32 *, 0x4C) * 0x18, 0x30809);
}
