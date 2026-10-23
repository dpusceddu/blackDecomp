#include "auto/prelude.h"

extern s32 func_00122E38(M2C_UNK *, s32);
extern M2C_UNK D_0048EFA8;
extern s32 func_00123020(M2C_UNK *, s32);
extern s32 func_00123248(M2C_UNK *);
extern void func_00123960(M2C_UNK *);
extern s32 func_00123980(M2C_UNK *, M2C_UNK, s32, s32);

void func_00122B60(s32 arg0) {
    func_00122E38(&D_0048EFA8, arg0);
}

void func_00122B88(s32 arg0) {
    func_00123020(&D_0048EFA8, arg0);
}

void func_00122BB0(void) {
    func_00123248(&D_0048EFA8);
}

void func_00122BD0(void) {
    func_00123960(&D_0048EFA8);
}

void func_00122BF0(s32 arg0, s32 arg1, s32 arg2) {
    func_00123980(&D_0048EFA8, 1, arg1, arg2);
}

void func_00122C20(s32 arg0, s32 arg1, s32 arg2) {
    func_00123980(&D_0048EFA8, 0, arg1, arg2);
}

void func_00122C50(s32 arg0, s32 arg1, s32 arg2) {
    func_00123980(&D_0048EFA8, 2, arg1, arg2);
}
