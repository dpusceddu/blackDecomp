#include "auto/prelude.h"

extern s32 func_001550F0();

s32 func_0015A8D0(void *arg0) {
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 4);
    if (M2C_FIELD(M2C_FIELD(temp_5, void **, 0xF0), s32 *, 0xC4) == 2) {
        if (func_001550F0(M2C_FIELD(temp_5, s32 *, 0xFC), M2C_FIELD(M2C_FIELD(arg0, void **, 8), s32 *, 0x64)) != 0) {
            M2C_FIELD(arg0, u16 *, 0x18) = (u16) (M2C_FIELD(arg0, u16 *, 0x18) + 1);
            return 1;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}
