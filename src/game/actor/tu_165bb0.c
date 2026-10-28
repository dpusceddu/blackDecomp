#include "include_asm.h"
#include "ps2/prelude.h"

void func_00165BB0(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xE) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s8 *, 0xC) = 0;
    M2C_FIELD(arg0, s8 *, 0xD) = 0;
    M2C_FIELD(arg0, s64 *, 0) = 0;
}

extern void *func_00107D20(u32);

#ifdef NON_MATCHING
// Unmatched: allocation loop and return scheduling differ.
void *func_00165BC8(void *arg0, s32 arg1) {
    s32 i;
    void *result;
    M2C_FIELD(arg0, u8 *, 0xC) = (u8) arg1;
    if ((u8) arg1 == 0) {
        M2C_FIELD(arg0, void **, 8) = 0;
        return 0;
    }
    result = func_00107D20(M2C_FIELD(arg0, u8 *, 0xC) * 4);
    M2C_FIELD(arg0, void **, 8) = result;
    for (i = 0; i < arg1; i++) {
        result = M2C_FIELD(arg0, void **, 8);
        M2C_FIELD((char *) result + i * 4, s32 *, 0) = 0;
    }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00165BC8);
#endif
