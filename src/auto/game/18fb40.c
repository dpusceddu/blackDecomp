#include "auto/prelude.h"

extern s32 func_0018E488();
extern s32 func_00190380(void *, s32, u8);
extern s32 func_0018D698(s32, M2C_UNK);

void func_0018FB40(void *arg0) {
    func_0018E488();
    func_00190380(arg0, M2C_FIELD(arg0, s32 *, 0x2C), M2C_FIELD(arg0, u8 *, 0x3C));
    func_0018D698(M2C_FIELD(arg0, s32 *, 4) + 0xD10, 0);
}
