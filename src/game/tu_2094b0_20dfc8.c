#include "auto/prelude.h"

extern s32 func_0027C278(s32);
extern s32 func_00209F98();
extern s32 func_0020BC00();
extern void * D_0040F544;
extern s32 func_00209FF8();
extern s32 func_00209EC8(s32, s32, s32);

void func_0020DFC8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_17;

    temp_17 = func_0027C278(arg1);
    func_00209F98(func_0020BC00(D_0040F544, 0), temp_17, arg2);
}

void func_0020E020(s32 arg0, s32 arg1) {
    s32 temp_16;

    temp_16 = func_0027C278(arg1);
    func_00209FF8(func_0020BC00(D_0040F544, 0), temp_16);
}

void func_0020E068(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_16;

    temp_16 = func_0020BC00(D_0040F544, 2);
    func_00209EC8(temp_16, func_0027C278(arg1), arg2);
}

void func_0020E0C8(s32 arg0, s32 arg1) {
    s32 temp_16;

    temp_16 = func_0020BC00(D_0040F544, 2);
    func_00209FF8(temp_16, func_0027C278(arg1));
}
