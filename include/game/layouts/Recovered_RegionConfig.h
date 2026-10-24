/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_REGIONCONFIG_H
#define RECOVERED_REGIONCONFIG_H
#include "ps2/prelude.h"

typedef struct Recovered_RegionConfig {
    u8 opaque_0[32];
    u8 field_20; /* PS2 +0x20 */
    u8 field_21; /* PS2 +0x21 */
    u8 field_22; /* PS2 +0x22 */
} Recovered_RegionConfig;
typedef char assert_Recovered_RegionConfig_20[(((int)&((Recovered_RegionConfig *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_RegionConfig_21[(((int)&((Recovered_RegionConfig *)0)->field_21) == 33) ? 1 : -1];
typedef char assert_Recovered_RegionConfig_22[(((int)&((Recovered_RegionConfig *)0)->field_22) == 34) ? 1 : -1];
#endif
