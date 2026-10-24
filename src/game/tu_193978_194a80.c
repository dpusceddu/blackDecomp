#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0018D608();
extern s32 func_0018AB08();
extern s32 func_00178F28();
extern s32 * func_00188F80();
extern s32 func_00193A28();

s32 func_00194A80(void **arg0, s32 *arg1) {
    s32 var_2;

    if (*arg1 == 2) {
        var_2 = 1;
        if (func_0018D608(*arg0 + 0xD10) != 0) {
            var_2 = 1;
            if (func_0018AB08(*arg0 + 0x150) != 0) {
                if (func_00178F28(func_00188F80(*arg0 + 0x150)) != 0) {
                    func_00193A28(arg0, 0x15, 0);
                }
                return 1;
            }
        }
        /* Duplicate return node #7. Try simplifying control flow for better match */
        return var_2;
    }
    var_2 = 0;
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00194B08);
