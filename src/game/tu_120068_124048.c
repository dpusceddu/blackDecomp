#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_0026F340();
extern s32 func_0027F640();
extern s32 func_0035D1A0();
extern s32 func_00123BC8();
extern M2C_UNK D_0048EFA8;

void func_00124048(void *arg0) {
    u8 sp[8];
    func_0026F340(sp);
    M2C_FIELD(arg0, s32 *, 0) = func_0027F640(sp);
    M2C_FIELD(arg0, s8 *, 0x6A5) = 0;
}

void func_00124080(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 4) = (f32) (M2C_FIELD(arg0, f32 *, 4) + fparg0);
}

s32 func_00124090(s32 arg0, s32 arg1) {
    return func_0035D1A0(arg0 + 8, arg1, 0x50);
}

void func_001240B0(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0x6A5) = arg1;
}

void func_001240B8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x58) = func_00123BC8(&D_0048EFA8);
}
