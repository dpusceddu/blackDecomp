#include "auto/prelude.h"

extern s32 func_00312C48();
extern void func_00313C48(void *arg0);

void * func_00313BF0(void *arg0) {
    s32 var_2;
    void *var_16;

    var_16 = arg0;
    if (var_16 == NULL) {
        var_16 = func_00312C48(0x48, 0x30808);
        var_2 = 2;
    } else {
        var_2 = 1;
    }
    M2C_FIELD(var_16, s32 *, 0x30) = var_2;
    func_00313C48(var_16);
    return var_16;
}
