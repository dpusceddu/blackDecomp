#include "auto/prelude.h"

#include "types_ghidra.h"
extern M2C_UNK D_0040A991;
extern s8 func_00364DE0();

s8 * func_003608B8(s8 *arg0) {
    s8 *var_16;
    s8 temp_4;

    var_16 = arg0;
    if (*arg0 != 0) {
        do {
            temp_4 = *var_16;
            if (M2C_FIELD((temp_4 + ((s32) &D_0040A991)), u8 *, 0) & 1) {
                *var_16 = func_00364DE0(temp_4);
            }
            var_16 += 1;
        } while (*var_16 != 0);
    }
    return arg0;
}
