/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ISSET160_H
#define RECOVERED_ISSET160_H
#include "ps2/prelude.h"

typedef struct Recovered_IsSet160 {
    u8 opaque_0[352];
    s32 field_160; /* PS2 +0x160 */
} Recovered_IsSet160;
typedef char assert_Recovered_IsSet160_160[(((int)&((Recovered_IsSet160 *)0)->field_160) == 352) ? 1 : -1];
#endif
