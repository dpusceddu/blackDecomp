#include "ps2/prelude.h"

void func_0032AB60(void *arg0, s32 arg1) {
    M2C_UNK (*temp_2)(void *);
    M2C_UNK (*temp_2_2)(void *);

    switch (arg1) {                                 /* irregular */
    case 1:
        temp_2 = M2C_FIELD(arg0, M2C_UNK (**)(void *), 0x20);
        if (temp_2 != NULL) {
            temp_2(arg0 + 0x50);
        }
        return;
    case 2:
        temp_2_2 = M2C_FIELD(arg0, M2C_UNK (**)(void *), 0x24);
        if (temp_2_2 != NULL) {
            temp_2_2(arg0 + 0x50);
        }
        break;
    }
}
