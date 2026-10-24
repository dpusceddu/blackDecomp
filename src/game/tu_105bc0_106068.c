#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "game/layouts/Recovered_FrontendLoadState.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_00106068(Recovered_FrontendLoadState *arg0) {
    M2C_FIELD(arg0, s64 *, 0x18) = 0;
    arg0->field_0 = 1;
    arg0->field_4 = 0;
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    return 1;
}
