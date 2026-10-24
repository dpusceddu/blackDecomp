/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_FRONTENDCALLBACKQUEUE_H
#define RECOVERED_FRONTENDCALLBACKQUEUE_H
#include "ps2/prelude.h"

typedef struct Recovered_FrontendCallbackQueue {
    u8 opaque_0[3592];
    s32 field_E08; /* PS2 +0xE08 */
    s32 field_E0C; /* PS2 +0xE0C */
    s32 field_E10; /* PS2 +0xE10 */
    u32 field_E14; /* PS2 +0xE14 */
} Recovered_FrontendCallbackQueue;
typedef char assert_Recovered_FrontendCallbackQueue_E08[(((int)&((Recovered_FrontendCallbackQueue *)0)->field_E08) == 3592) ? 1 : -1];
typedef char assert_Recovered_FrontendCallbackQueue_E0C[(((int)&((Recovered_FrontendCallbackQueue *)0)->field_E0C) == 3596) ? 1 : -1];
typedef char assert_Recovered_FrontendCallbackQueue_E10[(((int)&((Recovered_FrontendCallbackQueue *)0)->field_E10) == 3600) ? 1 : -1];
typedef char assert_Recovered_FrontendCallbackQueue_E14[(((int)&((Recovered_FrontendCallbackQueue *)0)->field_E14) == 3604) ? 1 : -1];
#endif
