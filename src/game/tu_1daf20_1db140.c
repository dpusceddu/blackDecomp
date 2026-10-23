#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001DD3E0(void *);

s32 func_001DB140(void *arg0) {
    u32 temp_3;

    temp_3 = M2C_FIELD(arg0, u32 *, 0x28);
    switch (temp_3) {
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
        M2C_FIELD(arg0, u32 *, 0x28) = 5U;
        /* fallthrough */
    case 5:
        if (func_001DD3E0(M2C_FIELD(arg0, void **, 0)) != 0) {
            M2C_FIELD(arg0, u32 *, 0x28) = 2U;
        case 0:
        case 2:
            return 1;
        }
    default:
        return 0;
    }
}
