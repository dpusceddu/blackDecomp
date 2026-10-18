#include "auto/prelude.h"

extern s32 func_00274FC8(s32);
extern s32 func_00274F80(s32);
extern s32 func_00274F60(s32);

s32 func_00282170(void *arg0) {
    func_00274FC8(arg0 + 0x38);
    M2C_FIELD(arg0, s32 *, 0x54) = 2;
    return 1;
}

s32 func_002821A8(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg2) {                                 /* irregular */
    case 0:
        return func_00274F80(arg0 + 0x1C);
    case 1:
        return func_00274F80(arg0 + 0x38);
    default:
        return 0;
    }
}

void func_002821F0(s32 arg0) {
    func_00274F60(arg0 + 0x38);
}
