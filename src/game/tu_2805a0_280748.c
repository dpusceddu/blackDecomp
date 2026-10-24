#include "ps2/prelude.h"

extern s32 func_002855A8();
extern s32 func_0027FE70();
extern void func_00280D70();

void func_00280748(void *arg0, void *arg1) {
    func_002855A8(arg0 + 0xB308, arg1 + 4);
    func_0027FE70(arg0, arg1 + 0x34);
    func_00280D70(arg0 + 0xCB94);
    M2C_FIELD(arg0, s32 *, 0xCB98) = 1;
    M2C_FIELD(arg0, s8 *, 0xCB9E) = 0;
}
