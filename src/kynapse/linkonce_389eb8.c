#include "ps2/prelude.h"

extern s32 D_0049AA48;
extern s32 func_00389F90();
extern s32 func_00370168();
extern M2C_UNK D_0049AA58;
extern M2C_UNK D_003E4700;

void func_00389EB8(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 8) = fparg0;
    M2C_FIELD(arg0, s8 *, 4) = 1;
}

f32 func_00389EC8(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 8);
}

s32 * func_00389ED0(void) {
    if (D_0049AA48 == 0) {
        func_00389F90();
        func_00370168(&D_0049AA48, "Q24Kaim13CEntityCanFly", &D_0049AA58);
    }
    return &D_0049AA48;
}

void * func_00389F20(void *arg0) {
    M2C_FIELD(arg0, s8 *, 4) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E4700;
    return arg0;
}
