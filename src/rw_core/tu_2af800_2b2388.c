#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_002AFCB8(s32 *, void *);

s32 func_002B2388(void *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 temp_18;
    s32 var_17;
    void *var_16;
    void *var_20;

    var_17 = arg2;
    if (arg0 != NULL) {
        var_20 = arg0 + 0x1C;
        if (arg3 > 0) {
            temp_18 = arg3 - 1;
            var_16 = var_20;
            do {
                var_20 += 0x20;
                var_17 = func_002B2388(M2C_FIELD(var_16, void **, 0x1C), arg1, func_002B2388(M2C_FIELD(var_16, void **, 0x18), arg1, func_002B2388(M2C_FIELD(var_16, void **, 0x14), arg1, func_002B2388(M2C_FIELD(var_16, void **, 0x10), arg1, func_002B2388(M2C_FIELD(var_16, void **, 0xC), arg1, func_002B2388(M2C_FIELD(var_16, void **, 8), arg1, func_002B2388(M2C_FIELD(var_16, void **, 4), arg1, func_002B2388(M2C_FIELD(var_16, void **, 0), arg1, var_17, temp_18), temp_18), temp_18), temp_18), temp_18), temp_18), temp_18), temp_18);
                var_16 += 0x20;
            } while ((s32) var_20 < (s32) (arg0 + 0x5C));
        } else {
            func_002AFCB8(&arg1[var_17], arg0);
            M2C_FIELD(arg0, s8 *, 0x18) = (s8) var_17;
            var_17 += 1;
        }
    }
    return var_17;
}
