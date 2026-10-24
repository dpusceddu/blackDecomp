#include "ps2/prelude.h"

extern s32 func_002726D0();
extern s32 func_0035E750();

void func_00165C40(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, u8 *, 0xC) != 0) {
        M2C_FIELD(((M2C_FIELD(arg0, u8 *, 0xD) * 4) + M2C_FIELD(arg0, s32 *, 8)), s32 *, 0) = arg1;
        M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) + 1);
    }
}

void func_00165C78(s64 *arg0) {
    u8 sp[24] __attribute__((aligned(16)));

    func_002726D0(*arg0, sp);
    *(u8 *)(sp + 16) = *(s32 *)(sp + 4);
    *(u8 *)(sp + 17) = *(s32 *)(sp + 5);
    *(s8 *)(sp + 18) = 0;
    func_0035E750((sp + 16));
}
