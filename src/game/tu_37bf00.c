#include "ps2/prelude.h"

extern s32 func_00323150();

s32 func_0037BF00(s32 arg0, s32 arg1) {
    return func_00323150(arg0, M2C_FIELD(arg0, s32 *, 0x40), 0, arg1);
}
