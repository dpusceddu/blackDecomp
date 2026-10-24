#include "ps2/prelude.h"

#include "types_ghidra.h"
extern M2C_UNK D_0042A630;

void func_001EA518(void *arg0, s32 arg1, s32 arg2) {
    void *temp_4;

    if (arg2 != 0) {
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) | (1 << arg1));
        temp_4 = (arg1 * 0x140) + ((s32) &D_0042A630);
        M2C_FIELD(temp_4, f32 *, 0x138) = -1.0f;
        M2C_FIELD(temp_4, s8 *, 0x13D) = 0;
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) & ~(1 << arg1));
}
