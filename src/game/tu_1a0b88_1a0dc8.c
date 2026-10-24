#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_001A0DC8(s32 *arg0) {
    s32 temp_3;
    s32 temp_4;
    s32 var_2;
    void *temp_2;

    temp_4 = *arg0;
    temp_3 = M2C_FIELD(M2C_FIELD(temp_4, void **, 0xC30), s32 *, 0x74);
    var_2 = temp_3 < 2;
    if (temp_3 != 1) {
        if ((var_2 != 0) && (temp_3 == 0)) {
            temp_2 = M2C_FIELD(temp_4, void **, 0x694);
            M2C_FIELD(temp_2, s8 *, 0x30) = 1;
            return (s32) temp_2;
        }
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return var_2;
    }
    var_2 = (s32) M2C_FIELD(temp_4, void **, 0x694);
    M2C_FIELD(var_2, s8 *, 0x30) = 0;
    return var_2;
}
