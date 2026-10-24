#include "ps2/prelude.h"

extern s32 func_0018E488();
extern s32 func_0018D698(s32, M2C_UNK);

void func_00190730(void *arg0) {
    func_0018E488();
    func_0018D698(M2C_FIELD(arg0, s32 *, 4) + 0xD10, 0);
}
