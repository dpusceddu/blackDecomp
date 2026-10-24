/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_QUEUEDACTIONEVENT_H
#define RECOVERED_QUEUEDACTIONEVENT_H
#include "ps2/prelude.h"

typedef struct Recovered_QueuedActionEvent {
    s32 field_0; /* PS2 +0x0 */
    u32 field_4; /* PS2 +0x4 */
} Recovered_QueuedActionEvent;
typedef char assert_Recovered_QueuedActionEvent_0[(((int)&((Recovered_QueuedActionEvent *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_QueuedActionEvent_4[(((int)&((Recovered_QueuedActionEvent *)0)->field_4) == 4) ? 1 : -1];
#endif
