#include "ps2/prelude.h"

extern s32 func_00368E58(s32);
extern s32 func_00368F08();

s32 func_00369F18(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        func_00368E58(arg2);
    }
    return 1;
}

s32 func_00369F40(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        func_00368F08(arg2);
    }
    return 1;
}
