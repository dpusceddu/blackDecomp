#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0018AC80(s32, M2C_UNK);
extern s32 func_00183160(s32);
extern s32 func_00193A28(void **, M2C_UNK, M2C_UNK);
extern s32 func_00193990(void **, M2C_UNK);

void func_001977F8(void **arg0) {
    func_0018AC80(*arg0 + 0xD18, 0);
    if (func_00183160(*arg0 + 0xD10) != 0) {
        func_00193A28(arg0, 0x1F, 0);
        return;
    }
    func_00193990(arg0, 1);
}
