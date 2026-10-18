#include "auto/prelude.h"

extern s32 func_0027C278(s32);
extern s32 func_00209F38();
extern s32 func_0020BC00();
extern void * D_0040F544;
extern s32 func_00209FF8();

void func_0020DCF8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = func_0027C278(arg1);
    func_00209F38(func_0020BC00(D_0040F544, 3), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s32 *, 4));
}

void func_0020DD48(void *arg0) {
    func_00209FF8(func_0020BC00(D_0040F544, 3), M2C_FIELD(arg0, s32 *, 8));
}

void func_0020DD88(void *arg0) {
    *M2C_FIELD(arg0, s16 **, 4) = 0;
}
