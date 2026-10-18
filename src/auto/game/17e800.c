#include "auto/prelude.h"

extern s32 func_00173610(void *);
extern s32 func_001A6840(s32, M2C_UNK, M2C_UNK);

s32 func_0017E800(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x82) == 0) {
        if (func_00173610(arg0 + 0x18) != 0) {
            return func_001A6840(M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), void **, 0x7C), s32 *, 0x330), 0, 0) == 0;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 1;
    }
    return 1;
}
