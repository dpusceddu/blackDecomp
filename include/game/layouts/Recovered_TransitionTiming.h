/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_TRANSITIONTIMING_H
#define RECOVERED_TRANSITIONTIMING_H
#include "ps2/prelude.h"

typedef struct Recovered_TransitionTiming {
    u8 opaque_0[8];
    s32 field_8; /* PS2 +0x8 */
} Recovered_TransitionTiming;
typedef char assert_Recovered_TransitionTiming_8[(((int)&((Recovered_TransitionTiming *)0)->field_8) == 8) ? 1 : -1];
#endif
