#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001AC040();
extern void * func_00135550(void *);
extern f32 func_0013EF28(void *);

f32 func_001AC398(void) {
    f32 var_f0;
    void **temp_2;

    temp_2 = func_001AC040();
    var_f0 = 0.0f;
    if (func_00135550(*temp_2) != NULL) {
        var_f0 = func_0013EF28(func_00135550(*temp_2));
    }
    return var_f0;
}
