#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0014EC40();
extern void * func_0014EC90(s32);
extern void func_0014D5F0(void *arg0, void *arg1);

s32 func_0014D548(void *arg0) {
    s32 var_2;
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 4);
    var_2 = 0;
    if (temp_5 != NULL) {
        var_2 = 0;
        if (M2C_FIELD(temp_5, s32 *, 0x37C) == M2C_FIELD(arg0, s32 *, 0xC)) {
            if ((u32) (M2C_FIELD(temp_5, s32 *, 0x38C) - 1) < 2U) {
                return 0;
            }
            var_2 = ((func_0014EC40(M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(temp_5, s128 *, 0xA0)) ^ 1) & 0xFF) == 0;
            /* Duplicate return node #6. Try simplifying control flow for better match */
            return var_2;
        }
    }
    return var_2;
}

void func_0014D5A8(void *arg0) {
    void *temp_2;

    temp_2 = func_0014EC90(M2C_FIELD(arg0, s32 *, 8));
    if (temp_2 != NULL) {
        func_0014D5F0(arg0, temp_2);
        return;
    }
    M2C_FIELD(arg0, s32 *, 4) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_14d3b8_14d548", func_0014D5F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_14d3b8_14d548", func_0014D638);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_14d3b8_14d548", func_0014D7F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_14d3b8_14d548", func_0014D8E8);

void func_0014D908(void* unused) {

}
