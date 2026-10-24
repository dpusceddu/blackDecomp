#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_0018C178(void *arg0, void *arg1) {
    u32 var_7;
    u32 var_7_2;
    void ***temp_3;
    void ***var_6;
    void ***var_6_2;
    void **temp_3_2;

    temp_3 = (void ***) (((s8 *) arg0) + 0xF0);
    M2C_FIELD(arg0, void **, 0xFC) = arg1;
    var_7 = 0;
    var_6 = temp_3;
    do {
        *var_6 = NULL;
        var_7 += 1;
        var_6 = (void ***) (((s8 *) var_6) + 4);
    } while (var_7 < 2U);
    M2C_FIELD(arg0, void **, 0xF0) = arg0;
    M2C_FIELD(arg0, void **, 0xF4) = (void *) ((void *) (((s8 *) arg0) + 0x70));
    var_6_2 = temp_3;
    var_7_2 = 0;
    do {
        temp_3_2 = *var_6_2;
        var_7_2 += 1;
        var_6_2 = (void ***) (((s8 *) var_6_2) + 4);
        *temp_3_2 = arg1;
    } while (var_7_2 < 2U);
    M2C_FIELD(arg0, s32 *, 0xF8) = 2;
    return 2;
}
