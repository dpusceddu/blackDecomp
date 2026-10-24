/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_GRAPHCONFIG_H
#define RECOVERED_GRAPHCONFIG_H
#include "ps2/prelude.h"

typedef struct Recovered_GraphConfig {
    u8 opaque_0[12];
    s32 field_C; /* PS2 +0xC */
    u8 opaque_10[16];
    s32 field_20; /* PS2 +0x20 */
} Recovered_GraphConfig;
typedef char assert_Recovered_GraphConfig_C[(((int)&((Recovered_GraphConfig *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_GraphConfig_20[(((int)&((Recovered_GraphConfig *)0)->field_20) == 32) ? 1 : -1];
#endif
