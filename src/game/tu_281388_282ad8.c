#include "ps2/prelude.h"

extern s32 func_00285880();
extern s32 func_00313FD0();

void func_00282AD8(void *arg0) {
    u32 var_18;
    void *var_16;

    if (M2C_FIELD(arg0, s32 *, 0x1038) != 0) {
        var_18 = 0;
        if (M2C_FIELD(arg0, u32 *, 0x1028) != 0) {
            var_16 = arg0 + 0x10;
            do {
                var_18 += 1;
                func_00285880(var_16);
                var_16 += 0x20;
            } while (var_18 < (u32) M2C_FIELD(arg0, u32 *, 0x1028));
        }
        func_00313FD0(M2C_FIELD(arg0, s32 *, 0x1038));
        M2C_FIELD(arg0, s32 *, 0x1038) = 0;
    }
    M2C_FIELD(arg0, s8 *, 0x102E) = 0;
    M2C_FIELD(arg0, s32 *, 0x103C) = 1;
}
