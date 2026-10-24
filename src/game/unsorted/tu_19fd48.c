#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0018D608(s32);
extern s32 func_00193990(void **, M2C_UNK);
extern s32 func_00193980();
extern s32 func_00193988();

s32 func_0019FD48(void *arg0, s32 *arg1) {
    if ((*arg1 == 4) && (func_0018D608(M2C_FIELD(arg0, s32 *, 0) + 0xD10) != 0)) {
        M2C_FIELD(arg0, s8 *, 0x28) = 1;
        return 0;
    }
    return 0;
}

void func_0019FD98(void **arg0) {
    if ((M2C_FIELD(M2C_FIELD(*arg0, void **, 0x694), u8 *, 0x3B) ^ 1) != 0) {
        func_00193990(arg0, 1);
    }
}

void func_0019FDD0(void **arg0) {
    func_00193980();
    M2C_FIELD(M2C_FIELD(*arg0, void **, 0x694), s8 *, 0x3B) = 1;
}

void func_0019FE08(void) {
    func_00193988();
}
