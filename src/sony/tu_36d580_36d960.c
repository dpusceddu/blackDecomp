#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0036ED30();

s32 func_0036D960(u8 *arg0, u8 *arg1, u32 arg2) {
    u32 var_7;
    u8 *var_4;
    u8 *var_5;
    u8 temp_3;

    var_4 = arg0;
    var_5 = arg1;
    var_7 = 0;
    if (arg2 != 0) {
        do {
            temp_3 = *var_5;
            var_7 += 1;
            var_5 += 1;
            *var_4 = temp_3;
            var_4 += 1;
        } while (var_7 < arg2);
    }
    return 0;
}

void func_0036D990(void) {
    func_0036ED30();
}

void func_0036D998(s32 arg0) {
    func_0036D990();
    func_00367480(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36d580_36d960", func_0036D9C0);
