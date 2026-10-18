#include "auto/prelude.h"

void * func_002CFE90(void *arg0, s32 arg1) {
    void *var_16;

    var_16 = M2C_FIELD(arg0, void **, 0x14);
    if (var_16 != NULL) {
        do {
            M2C_FIELD(var_16, M2C_UNK (**)(s32, s32, s32), 0x24)(arg1, M2C_FIELD(var_16, s32 *, 0), M2C_FIELD(var_16, s32 *, 4));
            var_16 = M2C_FIELD(var_16, void **, 0x34);
        } while (var_16 != NULL);
    }
    return arg0;
}
