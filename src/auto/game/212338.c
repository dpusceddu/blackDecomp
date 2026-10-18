#include "auto/prelude.h"

extern void * D_0040F544;
extern s32 func_0035CBC0();

void func_00212338(void) {
    void *temp_16;

    temp_16 = D_0040F544;
    func_0035CBC0(temp_16 + 0x3820, "OptionsMenu");
    if (M2C_FIELD(temp_16, s8 *, 0x3840) == 0) {
        M2C_FIELD(temp_16, s32 *, 0x388C) = 1;
        return;
    }
    M2C_FIELD(temp_16, s32 *, 0x3884) = 1;
}
