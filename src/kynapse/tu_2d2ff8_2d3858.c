#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_002D3858(void *arg0) {
    void **temp_5;
    void *temp_3;

    temp_5 = M2C_FIELD(arg0, void ***, 0xC);
    temp_3 = *temp_5;
    return M2C_FIELD(temp_3, s32 (**)(void *, void **), 0x5C)((void *) (((s8 *) temp_5) + M2C_FIELD(temp_3, s16 *, 0x58)), temp_5);
}
