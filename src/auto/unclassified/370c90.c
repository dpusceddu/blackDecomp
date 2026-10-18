#include "auto/prelude.h"

extern s32 func_00370DA8();
extern M2C_UNK func_003714B0;
extern M2C_UNK func_00370760;

s32 func_00370C90(void *arg0) {
    s32 var_2;
    void *temp_2;

    var_2 = 0;
    if (arg0 != NULL) {
        temp_2 = M2C_FIELD(arg0, void **, 4);
        var_2 = func_00370DA8(M2C_FIELD(temp_2, s32 *, 4), &func_003714B0, 1, arg0 + M2C_FIELD(temp_2, s16 *, 0), &func_00370760, arg0);
    }
    return var_2 != 0;
}
