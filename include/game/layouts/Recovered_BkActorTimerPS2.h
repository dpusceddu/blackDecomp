/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_BKACTORTIMERPS2_H
#define RECOVERED_BKACTORTIMERPS2_H
#include "ps2/prelude.h"

typedef struct Recovered_BkActorTimerPS2 {
    f32 field_0; /* PS2 +0x0 */
    s32 field_4; /* PS2 +0x4 */
} Recovered_BkActorTimerPS2;
typedef char assert_Recovered_BkActorTimerPS2_0[(((int)&((Recovered_BkActorTimerPS2 *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_BkActorTimerPS2_4[(((int)&((Recovered_BkActorTimerPS2 *)0)->field_4) == 4) ? 1 : -1];
#endif
