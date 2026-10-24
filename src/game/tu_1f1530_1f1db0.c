#include "ps2/prelude.h"

extern void func_001F1DF8(s32, s32, s32);
extern s32 func_0027C278(M2C_UNK *);

void func_001F1DB0(s32 arg0, M2C_UNK *arg1, s32 arg2) {
    func_001F1DF8(arg0, func_0027C278(arg1), arg2);
}
