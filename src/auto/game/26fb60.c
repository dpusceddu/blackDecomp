#include "auto/prelude.h"

extern s32 func_0026F908();

s32 func_0026FB60(s32 arg0, s32 arg1) {
    s32 temp_5;
    s32 var_2;

    temp_5 = arg1 & 0xFFFF;
    if (temp_5 == 0x13) {
        goto block_5;
    }
    if (temp_5 >= 0x14) {
        goto block_4;
    }
    var_2 = 0;
    if (temp_5 == 0) {
        goto block_8;
    }
    goto block_6;
block_4:
    if (temp_5 != 0x6F) {
        goto block_6;
    }
block_5:
    func_0026F908(arg0, 1);
    goto block_7;
block_6:
    func_0026F908(arg0, 0xD);
block_7:
    var_2 = 0xD;
block_8:
    return var_2;
}
