#include "auto/prelude.h"

extern s32 func_002726D0();
extern s32 func_00280E10();
extern s64 func_00272580();

void func_00281EE0(void *arg0, s64 *arg1, s32 arg2) {
    u8 sp[24] __attribute__((aligned(16)));
    s64 temp_5;

    temp_5 = *arg1;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s64 *, 0) = temp_5;
    if (arg2 != 0) {
        func_002726D0(temp_5, sp);
        if ((func_00280E10((s8) *(s32 *)(sp + 11), (sp + 16)) != 0) && (func_00280E10((s8) *(s32 *)(sp + 10), (sp + 17)) != 0)) {
            M2C_FIELD(arg0, u8 *, 0xC) = *(u8 *)(sp + 16);
            M2C_FIELD(arg0, s8 *, 0xD) = (s8) (*(u8 *)(sp + 17) - 1);
        } else {
            M2C_FIELD(arg0, s8 *, 0xD) = 0;
            M2C_FIELD(arg0, u8 *, 0xC) = 1U;
        }
        M2C_FIELD(arg0, s64 *, 0) = func_00272580(M2C_FIELD(arg0, s64 *, 0), 0, 9);
    }
}
