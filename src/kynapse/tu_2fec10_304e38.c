#include "include_asm.h"
#include "ps2/prelude.h"

#include "kynapse/layouts/Recovered_AIRouteFollower.h"
#include "kynapse/layouts/Recovered_RouteRequest.h"
#include "ps2/recovered_types.h"
extern void * func_00300278(Recovered_AIRouteFollower *, Recovered_RouteRequest *);

s32 func_00304E38(void *arg0, s32 arg1, void *arg2, void *arg3) {
    void **temp_2;
    void *temp_16;
    void *temp_18;
    void *temp_3;
    void *temp_9;

    temp_18 = func_00300278((Recovered_AIRouteFollower *) arg0, (Recovered_RouteRequest *) arg2);
    temp_16 = func_00300278((Recovered_AIRouteFollower *) arg0, (Recovered_RouteRequest *) arg3);
    if (temp_18 != NULL) {
        if (temp_16 != NULL) {
            temp_3 = M2C_FIELD(arg0, void **, 0);
            temp_2 = M2C_FIELD(temp_3, void **(**)(void *), 0x84)((void *) (((s8 *) arg0) + M2C_FIELD(temp_3, s16 *, 0x80)));
            temp_9 = *temp_2;
            return M2C_FIELD(temp_9, s32 (**)(void *, s32, void *, void *, s32, void *), 0x14)((void *) (((s8 *) temp_2) + M2C_FIELD(temp_9, s16 *, 0x10)), M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 0x14), temp_18, temp_16, arg1, temp_9);
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}
