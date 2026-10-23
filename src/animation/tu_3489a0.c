#include "auto/prelude.h"

void func_003489A0(void) {

}

s32 * func_003489A8(void *arg0) {
    s16 temp_4;
    s32 *var_5;
    s32 temp_3;
    void *temp_2;

    var_5 = NULL;
    if (arg0 != NULL) {
        temp_2 = M2C_FIELD(arg0, void **, 4);
        if (temp_2 != NULL) {
            temp_3 = M2C_FIELD(temp_2, s32 *, 0x1C);
            if (temp_3 != 0) {
                temp_4 = M2C_FIELD(arg0, s16 *, 8);
                if (temp_4 != -1) {
                    var_5 = temp_3 + (temp_4 * 0x10);
                }
            }
        }
    }
    return var_5;
}
