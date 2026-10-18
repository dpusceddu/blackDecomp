#include "auto/prelude.h"

extern s32 func_001D76E8();
extern s32 func_001D7BB8();
extern s32 func_00281BB8();

s32 func_001D5EA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x84);
    switch (temp_3) {                               /* irregular */
    case 1:
        M2C_FIELD(arg0, s64 *, 0x1A8) = (s64) arg2;
        M2C_FIELD(arg0, s32 *, 0x1B4) = arg4;
        M2C_FIELD(arg0, s32 *, 0x1B0) = arg3;
        if (func_001D76E8(arg4, arg3, 1, arg2) == 0) {
            return 0;
        }
        M2C_FIELD(arg0, s32 *, 0x78) = func_001D7BB8(M2C_FIELD(arg0, s32 *, 0x1B4), arg1);
        M2C_FIELD(arg0, s32 *, 0x84) = 2;
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    case 2:
        func_00281BB8(arg0 + 0x94, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x80) = 0;
        return 1;
    default:
        return 0;
    }
}
