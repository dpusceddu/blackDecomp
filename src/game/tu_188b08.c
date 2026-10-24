#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_00188B08(void *arg0) {
    void *temp_3;
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 0x3A8);
    if (temp_5 != NULL) {
        temp_3 = M2C_FIELD(temp_5, void **, 0x60);
        return M2C_FIELD(temp_3, s32 (**)(void *, void *), 0x3C)((void *) (((s8 *) temp_5) + M2C_FIELD(temp_3, s16 *, 0x38)), temp_5);
    }
    return 1;
}
