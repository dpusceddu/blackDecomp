#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001E36A0(void *);
extern s32 func_001E3500(void *);
extern s32 func_00280B10(void *);
extern s32 func_00280100(s32, void *);
extern void * D_0040F510;

s32 func_001E3BB0(void *arg0) {
    s32 var_18;
    u32 temp_3;
    void *temp_5;
    void *var_16;

    temp_3 = M2C_FIELD(arg0, u32 *, 0x35C);
    switch (temp_3) {
    case 1:
    case 2:
    case 3:
        var_16 = arg0 + 0x250;
        var_18 = 3;
        do {
            if (M2C_FIELD(var_16, u8 *, 0x2C) != 0) {
                func_001E36A0(var_16);
            }
            var_18 -= 1;
            func_001E3500(var_16);
            var_16 += 0x30;
        } while (var_18 >= 0);
        M2C_FIELD(arg0, u32 *, 0x35C) = 4U;
        /* fallthrough */
    case 4:
        if (func_00280B10(arg0) != 0) {
            M2C_FIELD(arg0, u32 *, 0x35C) = 5U;
        case 5:
            temp_5 = M2C_FIELD(arg0, void **, 0x364);
            if (temp_5 != NULL) {
                if (func_00280100((s32) D_0040F510, temp_5) != 0) {
                    M2C_FIELD(arg0, void **, 0x364) = NULL;
                    goto block_12;
                }
                goto block_14;
            }
block_12:
            M2C_FIELD(arg0, s32 *, 0x36C) = 0;
            M2C_FIELD(arg0, u32 *, 0x35C) = 6U;
        case 0:
        case 6:
            return 1;
        }
    default:
block_14:
        return 0;
    }
}
