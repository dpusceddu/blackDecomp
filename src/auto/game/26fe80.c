#include "auto/prelude.h"

extern s32 func_0026F908();

s32 func_0026FE80(s32 arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = arg1 & 0xFFFF;
    switch (temp_5) {                               /* irregular */
    case 0x0:
        return 0;
    case 0x14:
    case 0x16:
        func_0026F908(arg0, 9);
block_12:
        return 0xD;
    case 0x6F:
    case 0x13:
        func_0026F908(arg0, 1);
        goto block_12;
    default:
        func_0026F908(arg0, 0xD);
        goto block_12;
    }
}

s32 func_0026FF10(s32 arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = arg1 & 0xFFFF;
    switch (temp_5) {                               /* irregular */
    case 0x0:
        return 0;
    case 0x16:
    case 0x14:
    case 0x2:
        func_0026F908(arg0, 9);
block_15:
        return 0xD;
    case 0x13:
    case 0x6F:
        func_0026F908(arg0, 1);
        goto block_15;
    default:
        func_0026F908(arg0, 0xD);
        goto block_15;
    }
}
