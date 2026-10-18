#include "auto/prelude.h"

s32 func_003183C0(s32 arg0) {
    s32 var_2;
    void *var_3;

    var_3 = M2C_FIELD(arg0, void **, 4);
    var_2 = 0;
    if (var_3 != arg0) {
        do {
            var_3 = M2C_FIELD(var_3, void **, 4);
            var_2 += 1;
        } while (var_3 != arg0);
    }
    return var_2;
}
