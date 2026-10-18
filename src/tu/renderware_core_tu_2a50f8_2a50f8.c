#include "auto/prelude.h"
#include "renderware_core/stream.h"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES


s32 func_002A50F8(RwChunkHeaderPS2 *header) {
    s32 temp_2;

    temp_2 = header->type;
    switch (temp_2) {
    case 1:
    case 2:
    case 3:
    case 13:
    case 19:
        return 0;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 14:
    case 15:
    case 16:
    case 18:
    case 20:
    case 26:
        return 1;
    default:
        return 0;
    }
}
