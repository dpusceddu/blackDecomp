#include "auto/prelude.h"

extern u8 D_0040EAE0;
extern void * D_0040F544;
extern s32 func_0035CBC0();
extern M2C_UNK D_0048EF88;

s32 func_00103FF0(s32 arg0) {
    u8 var_2;
    void *temp_16;

    if ((arg0 == 0) || (var_2 = D_0040EAE0, (var_2 != 0))) {
        temp_16 = D_0040F544;
        func_0035CBC0((s32) (temp_16 + 0x3820), (s32) &D_0048EF88);
        var_2 = 1;
        if (M2C_FIELD(temp_16, s8 *, 0x3840) == 0) {
            M2C_FIELD(temp_16, s32 *, 0x388C) = 1;
        } else {
            M2C_FIELD(temp_16, s32 *, 0x3884) = 1;
        }
    }
    return (s32) var_2;
}
