#include "auto/prelude.h"

extern s32 func_00316618();
extern s32 func_003165C8();

s32 func_00315278(s32 arg0, s32 arg1, s32 arg2) {
    if (func_00316618(arg0, arg1) != 0) {
        return (func_003165C8(arg0, arg2) == 0) ? 0 : arg0;
    }
    return 0;
}
