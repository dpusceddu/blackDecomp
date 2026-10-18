#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_0026F908();

s32 func_0026FA70(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_5;

    if (arg1 >= 0) {
        if (arg2 != 0) {
            M2C_FIELD(arg2, s32 *, 0) = arg1;
        }
        return 0;
    }
    temp_5 = arg1 & 0xFFFF;
    if ((temp_5 == 0x13) || (temp_5 == 0x6F)) {
        func_0026F908(arg0, 1);
    } else {
        func_0026F908(arg0, 0xD);
    }
    return 0xD;
}

s32 func_0026FAD0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_5;

    if (arg1 >= 0) {
        if (arg2 != 0) {
            M2C_FIELD(arg2, s32 *, 0) = arg1;
        }
        return 0;
    }
    temp_5 = arg1 & 0xFFFF;
    switch (temp_5) {                               /* irregular */
    case 0x1C:
        func_0026F908(arg0, 0xB);
        break;
    case 0x6F:
    case 0x13:
        func_0026F908(arg0, 1);
        break;
    default:
        func_0026F908(arg0, 0xD);
        break;
    }
    return 0xD;
}
