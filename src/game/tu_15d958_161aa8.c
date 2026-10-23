#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * func_00160E70(s32 *);
extern s32 * func_00107D20(s32);

s32 * func_00161AA8(s32 *arg0, s32 arg1) {
    s32 *temp_2;
    s32 *temp_2_2;

    temp_2_2 = func_00160E70(arg0);
    if (arg1 <= 0) {
        M2C_FIELD(arg0, s32 **, 0x24) = NULL;
        return temp_2_2;
    }
    temp_2 = func_00107D20(arg1 * 4);
    M2C_FIELD(arg0, s32 **, 0x24) = temp_2;
    return temp_2;
}
