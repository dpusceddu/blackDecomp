#include "auto/prelude.h"

extern void func_0035EBB0(void *);
extern void * D_003D6944;
extern s32 func_00364AB8(void *, s32, s32);
extern void func_0035EC10(void *);
extern s32 func_003639A0(void *, s32);
extern s32 func_003640D0(void *, s32);

s32 func_0035E778(s32 arg0, s32 arg1) {
    s32 temp_17;

    func_0035EBB0(D_003D6944);
    temp_17 = func_00364AB8(D_003D6944, arg0, arg1);
    func_0035EC10(D_003D6944);
    return temp_17;
}

s32 func_0035E7D8(s32 arg0) {
    s32 temp_16;

    func_0035EBB0(D_003D6944);
    temp_16 = func_003639A0(D_003D6944, arg0);
    func_0035EC10(D_003D6944);
    return temp_16;
}

void func_0035E828(s32 arg0) {
    func_0035EBB0(D_003D6944);
    func_003640D0(D_003D6944, arg0);
    func_0035EC10(D_003D6944);
}
