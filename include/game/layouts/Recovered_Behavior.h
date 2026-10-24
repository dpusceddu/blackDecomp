/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_BEHAVIOR_H
#define RECOVERED_BEHAVIOR_H
#include "ps2/prelude.h"

typedef struct Recovered_Behavior {
    void * field_0; /* PS2 +0x0 */
    u32 field_4; /* PS2 +0x4 */
    u32 field_8; /* PS2 +0x8 */
} Recovered_Behavior;
typedef char assert_Recovered_Behavior_0[(((int)&((Recovered_Behavior *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Behavior_4[(((int)&((Recovered_Behavior *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_Behavior_8[(((int)&((Recovered_Behavior *)0)->field_8) == 8) ? 1 : -1];
#endif
