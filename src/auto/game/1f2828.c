#include "auto/prelude.h"

extern s32 func_001F1B98(void *, s32);
extern void * D_0040F518;
extern s32 func_001F1C00();

void func_001F2828(void) {

}

s32 func_001F2830(void) {
    return 1;
}

void func_001F2838(s32 arg0, s8 arg1, s32 arg2) {
    func_001F1B98(D_0040F518 + (arg1 * 0xA8), arg2);
}

s32 func_001F2870(s32 arg0, s8 arg1) {
    return M2C_FIELD(((arg1 * 0xA8) + D_0040F518), s32 *, 0x8C);
}

void func_001F2898(s32 arg0, s8 arg1, s32 arg2) {
    func_001F1C00(D_0040F518 + (arg1 * 0xA8), arg2);
}
