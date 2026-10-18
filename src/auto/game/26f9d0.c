#include "auto/prelude.h"

extern s32 func_0026F908();

s32 func_0026F9D0(s32 arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = arg1 & 0xFFFF;
    switch (temp_5) {                               /* irregular */
    case 0x0:
        return 0;
    case 0x6F:
    case 0x13:
        func_0026F908(arg0, 1);
block_13:
        return 0xD;
    case 0x1C:
        func_0026F908(arg0, 0xB);
        goto block_13;
    case 0x17:
        func_0026F908(arg0, 0xC);
        goto block_13;
    default:
        func_0026F908(arg0, 0xD);
        goto block_13;
    }
}
