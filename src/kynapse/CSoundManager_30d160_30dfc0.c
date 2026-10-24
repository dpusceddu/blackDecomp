#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * func_002E7610(void *, s8 *, s32, s32, s32, s32);
extern M2C_UNK D_00455D00;
extern void * func_0030D160();
extern M2C_UNK D_003E5E40;
extern M2C_UNK * D_00455E10;

void * func_0030DFC0(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = (M2C_UNK *)0xFFFF;
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            return func_002E7610(&D_00455D00, "CSoundManager", (s32) func_0030D160, 0, 1, 0);
        }
        var_2 = &D_003E5E40;
        D_00455E10 = &D_003E5E40;
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return var_2;
    }
    return var_2;
}
