/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003E07B8_H
#define RECOVERED_VTABLE_003E07B8_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003E07B8 {
    u8 opaque_0[4];
    f32 field_4; /* PS2 +0x4 */
    f32 field_8; /* PS2 +0x8 */
    u8 opaque_C[4];
    f32 field_10; /* PS2 +0x10 */
    u8 opaque_14[12];
    f32 field_20; /* PS2 +0x20 */
} Recovered_Vtable_003E07B8;
typedef char assert_Recovered_Vtable_003E07B8_4[(((int)&((Recovered_Vtable_003E07B8 *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E07B8_8[(((int)&((Recovered_Vtable_003E07B8 *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E07B8_10[(((int)&((Recovered_Vtable_003E07B8 *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E07B8_20[(((int)&((Recovered_Vtable_003E07B8 *)0)->field_20) == 32) ? 1 : -1];
#endif
