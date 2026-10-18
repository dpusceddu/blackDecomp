#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_0029CF98();

s32 func_0026F258(void) {
    u32 temp_2;

    temp_2 = func_0029CF98();
    switch (temp_2) {
    case 0:
        return 2;
    case 1:
        return 1;
    case 2:
        return 4;
    case 3:
        return 5;
    case 4:
        return 3;
    case 5:
        return 6;
    case 6:
        return 0xA;
    case 7:
        return 9;
    default:
        return 0;
    }
}
