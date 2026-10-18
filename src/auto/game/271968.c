#include "auto/prelude.h"

extern s32 func_0028F618(s32);
extern s32 func_0028F718(s32);
extern s32 func_0028FA60(s32);

s32 func_00271968(s32 arg0, s32 arg1, s32 arg2) {
    func_0028F618(arg2 + 0xB8);
    return 1;
}

s32 func_00271988(s32 arg0, s32 arg1, s32 arg2) {
    func_0028F718(arg2 + 0xB8);
    return 1;
}

s32 func_002719A8(s32 arg0) {
    return func_0028FA60(arg0 + 0xB8) <= 0xFFFF;
}
