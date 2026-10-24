#include "ps2/prelude.h"

extern s32 func_001B37C8();
extern s32 D_0040F4D8;

void func_00149AC8(void *arg0) {
    s32 var_16;
    u16 *temp_3;

    var_16 = 0;
    if (M2C_FIELD(arg0, u8 *, 0x1F6) != 0) {
        do {
            temp_3 = (var_16 * 2) + M2C_FIELD(arg0, s32 *, 0x1B0);
            if (*temp_3 != 0xFFFF) {
                func_001B37C8(D_0040F4D8 + 0x33C40, *temp_3);
            }
            var_16 += 1;
        } while (var_16 < (s32) M2C_FIELD(arg0, u8 *, 0x1F6));
    }
}
