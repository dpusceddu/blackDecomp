#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * func_0030D0E0(void *, s8 *, s32);
extern M2C_UNK D_00455BE8;
extern void * func_003067A0(void *);
extern M2C_UNK D_003F07A0;
extern M2C_UNK * D_00455CF8;

void * func_0030B750(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = (M2C_UNK *)0xFFFF;
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            return func_0030D0E0(&D_00455BE8, "CGapDynamicAvoidance", (s32) func_003067A0);
        }
        var_2 = &D_003F07A0;
        D_00455CF8 = &D_003F07A0;
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return var_2;
    }
    return var_2;
}
