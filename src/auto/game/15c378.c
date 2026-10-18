#include "auto/prelude.h"

extern void * func_0015D248(void **arg0, s8 arg1, s32 arg2);
extern void ** D_0040F4E0;
extern s32 func_00155178(void *, s32, u8);

s32 func_0015C378(void *arg0) {
    s32 var_2;
    s8 *temp_3;
    void *temp_2;

    temp_3 = M2C_FIELD(arg0, s8 **, 0x24);
    var_2 = 0;
    if (temp_3 != NULL) {
        temp_2 = func_0015D248(D_0040F4E0, *temp_3, 0);
        var_2 = func_00155178(arg0, M2C_FIELD(temp_2, s32 *, 0x64), M2C_FIELD(temp_2, u8 *, 0x60));
    }
    return var_2;
}
