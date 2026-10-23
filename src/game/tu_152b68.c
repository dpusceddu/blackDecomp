#include "auto/prelude.h"

extern void * func_001AFD80();

s32 func_00152B68(void *arg0) {
    s32 var_2;
    void *temp_2;

    temp_2 = func_001AFD80(arg0 + 0x1A0, M2C_FIELD(arg0, s32 *, 0x118));
    var_2 = 0;
    if (temp_2 != NULL) {
        if (M2C_FIELD(temp_2, u8 *, 0xCE) == 0) {
            return 0;
        }
        var_2 = M2C_FIELD(M2C_FIELD(temp_2, void **, 0xC4), s32 *, 0x40) == 1;
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return var_2;
    }
    return var_2;
}
