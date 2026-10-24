#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_0042A1E0;
extern M2C_UNK D_004199E0;

s32 * func_001D1DC8(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6, void *arg7) {
    s32 *temp_2;
    void *temp_3;

    temp_3 = arg0 + 0xF;
    temp_2 = D_0042A1E0 + ((s32) &D_004199E0);
    D_0042A1E0 += ((s32) (((s32) temp_3 > -1) ? temp_3 : (arg0 + 0x1E)) >> 4) * 0x10;
    return temp_2;
}
