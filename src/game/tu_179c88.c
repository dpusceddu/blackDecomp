#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern u8 func_0017A0A8(RecoveredRouteRequest *); /* AIMovement_AdvanceRouteRequest */

void func_00179C88(void *arg0) {
    do {

    } while (func_0017A0A8((RecoveredRouteRequest *) arg0) != 0);
}
