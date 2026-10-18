#include "auto/prelude.h"

void func_0034F328(void *arg0, s32 arg1) {
    s32 temp_2;
    s32 var_2;
    void *var_4;

    var_4 = arg0;
    if (var_4 != NULL) {
        do {
            temp_2 = M2C_FIELD(var_4, s32 *, 0);
            if (arg1 != 0) {
                var_2 = temp_2 | 0x1000;
            } else {
                var_2 = temp_2 & ~0x1000;
            }
            M2C_FIELD(var_4, s32 *, 0) = var_2;
            var_4 = M2C_FIELD(var_4, void **, 0x9AC);
        } while (var_4 != NULL);
    }
}
