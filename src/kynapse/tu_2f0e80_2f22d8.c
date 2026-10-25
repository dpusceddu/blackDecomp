#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00390818();
extern M2C_UNK D_003ECA80;
extern s32 D_003EC8F0;
extern s32 func_002F1EB0(M2C_UNK, M2C_UNK);

s32 func_002F22D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00390818(arg0, arg1, arg2, arg3, 0, 0);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003ECA80;
    return arg0;
}


void func_002F23E8(void) {
    D_003EC8F0 = 0;
}

void func_002F23F8(void) {
    func_002F1EB0(1, 0xFFFF);
}

void func_002F2418(void) {
    func_002F1EB0(0, 0xFFFF);
}
