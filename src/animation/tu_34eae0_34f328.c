#include "include_asm.h"
#include "ps2/prelude.h"
#include "animation/instance.h"

void func_0034F328(void *arg0, s32 arg1) {
    s32 temp_2;
    s32 var_2;
    void *var_4;

    var_4 = arg0;
    if (var_4 != NULL) {
        do {
            temp_2 = ((BkModAnimationInstancePS2*)var_4)->flags;
            if (arg1 != 0) {
                var_2 = temp_2 | 0x1000;
            } else {
                var_2 = temp_2 & ~0x1000;
            }
            ((BkModAnimationInstancePS2*)var_4)->flags = var_2;
            var_4 = ((BkModAnimationInstancePS2*)var_4)->next;
        } while (var_4 != NULL);
    }
}
