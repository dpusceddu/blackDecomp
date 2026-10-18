#include "auto/prelude.h"

void func_00241C40(void) {

}

void func_00241C48(s32 arg0, void *arg1) {
    s32 temp_3;
    void *temp_3_2;

    temp_3 = M2C_FIELD(arg1, s32 *, 0);
    if (!((temp_3 >> 1) & 1)) {
        temp_3_2 = M2C_FIELD(arg1, void **, 4);
        M2C_FIELD(arg1, s32 *, 0) = (s32) (temp_3 | 2);
        M2C_FIELD(temp_3_2, M2C_UNK (**)(void *), 0x74)(arg1 + M2C_FIELD(temp_3_2, s16 *, 0x70));
    }
}
