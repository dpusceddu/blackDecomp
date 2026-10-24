#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern u8 func_0017A0A8(RecoveredRouteRequest *); /* AIMovement_AdvanceRouteRequest */

void func_00179C88(void *arg0) {
    do {

    } while (func_0017A0A8((RecoveredRouteRequest *) arg0) != 0);
}
