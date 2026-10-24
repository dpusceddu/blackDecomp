/* Translation unit tu_268c68 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

s32 func_00268E90(void *arg0, s32 arg1) {
    return M2C_FIELD(arg0, s32 *, 0x114) + (arg1 << 6);
}

void func_00268EA0(void *arg0) {
    s16 temp_6;
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x28);
    temp_6 = M2C_FIELD(temp_3, s16 *, 0x30);
    M2C_FIELD(temp_3, M2C_UNK (**)(void *, M2C_UNK, s16), 0x34)(arg0 + temp_6, 0, temp_6);
}

/* Assembly between the functions: func_00268ED0 (336 bytes), func_00269020 (128 bytes), func_002690A0 (232 bytes), func_00269188 (848 bytes) */

s32 func_002694D8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x1C) = 1;
    return 0;
}
