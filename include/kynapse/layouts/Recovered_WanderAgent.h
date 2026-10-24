/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_WANDERAGENT_H
#define RECOVERED_WANDERAGENT_H
#include "ps2/prelude.h"

typedef struct Recovered_WanderAgent {
    void * field_0; /* PS2 +0x0 */
    void * field_4; /* PS2 +0x4 */
    u8 opaque_8[4];
    s32 field_C; /* PS2 +0xC */
    f32 field_10; /* PS2 +0x10 */
    f32 field_14; /* PS2 +0x14 */
    f32 field_18; /* PS2 +0x18 */
    s32 field_1C; /* PS2 +0x1C */
    s32 field_20; /* PS2 +0x20 */
    void * field_24; /* PS2 +0x24 */
    void * field_28; /* PS2 +0x28 */
    u8 field_2C; /* PS2 +0x2C */
} Recovered_WanderAgent;
typedef char assert_Recovered_WanderAgent_0[(((int)&((Recovered_WanderAgent *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_WanderAgent_4[(((int)&((Recovered_WanderAgent *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_WanderAgent_C[(((int)&((Recovered_WanderAgent *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_WanderAgent_10[(((int)&((Recovered_WanderAgent *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_WanderAgent_14[(((int)&((Recovered_WanderAgent *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_WanderAgent_18[(((int)&((Recovered_WanderAgent *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_WanderAgent_1C[(((int)&((Recovered_WanderAgent *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_WanderAgent_20[(((int)&((Recovered_WanderAgent *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_WanderAgent_24[(((int)&((Recovered_WanderAgent *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_WanderAgent_28[(((int)&((Recovered_WanderAgent *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_WanderAgent_2C[(((int)&((Recovered_WanderAgent *)0)->field_2C) == 44) ? 1 : -1];
#endif
