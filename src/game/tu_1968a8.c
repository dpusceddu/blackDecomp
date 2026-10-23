#include "auto/prelude.h"

extern s32 func_00188F10(s32);
extern s32 func_00193990(void **, M2C_UNK);
extern s32 func_00193980();
extern s32 func_0018AC80(s32, M2C_UNK);
extern s32 func_00193988();

void func_001968A8(void **arg0) {
    if (func_00188F10(*arg0 + 0x150) != 0) {
        func_00193990(arg0, 1);
    }
}

void func_001968E8(s32 *arg0) {
    func_00193980();
    func_0018AC80(*arg0 + 0xD18, 1);
}

void func_00196920(s32 *arg0) {
    func_00193988();
    func_0018AC80(*arg0 + 0xD18, 0);
}
