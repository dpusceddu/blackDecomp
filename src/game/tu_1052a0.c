#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"

void func_001052A0(void *arg0, void *arg1) {
    void *temp_3;
    void *temp_3_2;
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 4);
    if (temp_5 != NULL) {
        temp_3 = M2C_FIELD(temp_5, void **, 4);
        M2C_FIELD(temp_3, M2C_UNK (**)(void *, void *), 0x1C)((void *) (((s8 *) temp_5) + M2C_FIELD(temp_3, s16 *, 0x18)), temp_5);
    }
    M2C_FIELD(arg0, void **, 4) = arg1;
    if (arg1 != NULL) {
        temp_3_2 = M2C_FIELD(arg1, void **, 4);
        M2C_FIELD(temp_3_2, M2C_UNK (**)(void *), 0xC)((void *) (((s8 *) arg1) + M2C_FIELD(temp_3_2, s16 *, 8)));
    }
}
