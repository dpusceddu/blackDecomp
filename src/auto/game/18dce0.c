#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_0018DCE0(void *arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 4);
    switch (temp_2) {
    case 36:
    case 37:
        return 0x22;
    case 38:
        return 0x26;
    case 39:
        return 0x33;
    case 40:
        return 0x36;
    case 41:
        return 0x31;
    case 42:
        return 0x2A;
    case 29:
        return 0x46;
    case 30:
        return 0x47;
    case 31:
        return 0x48;
    default:
        return 0;
    }
}
