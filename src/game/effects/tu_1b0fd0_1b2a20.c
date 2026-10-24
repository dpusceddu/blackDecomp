#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001B1518(void *);

void func_001B2A20(s32 arg0, s32 arg1, u8 arg2) {
    s32 temp_6;
    s32 var_17;
    void *var_16;

    temp_6 = arg2 & 0xFF;
    if (temp_6 != 0) {
        var_16 = arg1 + 0xB0;
        var_17 = temp_6;
        do {
            if (M2C_FIELD(var_16, s32 *, 0x60) != 0) {
                func_001B1518(var_16);
            }
            var_17 -= 1;
            var_16 += 0x130;
        } while (var_17 != 0);
    }
}
