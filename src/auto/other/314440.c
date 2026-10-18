#include "auto/prelude.h"

extern s32 func_00318250(s32);

s32 func_00314440(s32 arg0) {
    return (~func_00318250(arg0 + 0xC) == 0) ? 0 : arg0;
}
