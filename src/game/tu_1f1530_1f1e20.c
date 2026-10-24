#include "ps2/prelude.h"

extern void func_001F1E90(M2C_UNK *, s32);
extern s32 func_0027C278(M2C_UNK *);
extern void func_001F1EB8(s32, s32);

void func_001F1E20(M2C_UNK *arg0, M2C_UNK *arg1) {
    func_001F1E90(arg0, func_0027C278(arg1));
}

void func_001F1E58(s32 arg0, M2C_UNK *arg1) {
    func_001F1EB8(arg0, func_0027C278(arg1));
}
