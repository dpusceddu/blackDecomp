#include "auto/prelude.h"

void func_002E6F90(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, M2C_UNK (**)(s32), 0x10)(arg1);
}

void * func_002E6FB0(void *arg0, s32 arg1) {
    void *temp_3;
    void *var_2;

    temp_3 = M2C_FIELD(arg0, void **, 0);
    var_2 = M2C_FIELD(temp_3, void *(**)(void *), 0x1C)(arg0 + M2C_FIELD(temp_3, s16 *, 0x18));
    if (var_2 == NULL) {
        M2C_FIELD(arg0, M2C_UNK (**)(s32), 0x14)(arg1);
        var_2 = arg0;
    }
    return var_2;
}

void func_002E7008(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, M2C_UNK (**)(s32), 0x14)(arg1);
}
