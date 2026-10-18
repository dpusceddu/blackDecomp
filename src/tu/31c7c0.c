#include "auto/prelude.h"

extern void * func_00312C48();
extern s32 func_00312C70(void *);

void func_0031C7C0(void *arg0) {
    M2C_FIELD(arg0, void **, 0x50) = func_00312C48(M2C_FIELD(arg0, s32 *, 0x4C) * 0x18, 0x30809);
}

void func_0031C800(void *arg0) {
    func_00312C70(M2C_FIELD(arg0, void **, 0x50));
}
