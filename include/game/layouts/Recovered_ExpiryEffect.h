/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_EXPIRYEFFECT_H
#define RECOVERED_EXPIRYEFFECT_H
#include "ps2/prelude.h"

typedef struct Recovered_ExpiryEffect {
    u8 opaque_0[272];
    f32 field_110; /* PS2 +0x110 */
    u8 field_114; /* PS2 +0x114 */
    u8 field_115; /* PS2 +0x115 */
} Recovered_ExpiryEffect;
typedef char assert_Recovered_ExpiryEffect_110[(((int)&((Recovered_ExpiryEffect *)0)->field_110) == 272) ? 1 : -1];
typedef char assert_Recovered_ExpiryEffect_114[(((int)&((Recovered_ExpiryEffect *)0)->field_114) == 276) ? 1 : -1];
typedef char assert_Recovered_ExpiryEffect_115[(((int)&((Recovered_ExpiryEffect *)0)->field_115) == 277) ? 1 : -1];
#endif
