/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003E1988_H
#define RECOVERED_VTABLE_003E1988_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003E1988 {
    u8 opaque_0[4];
    u32 field_4; /* PS2 +0x4 */
    u8 opaque_8[24];
    void * field_20; /* PS2 +0x20 */
} Recovered_Vtable_003E1988;
typedef char assert_Recovered_Vtable_003E1988_4[(((int)&((Recovered_Vtable_003E1988 *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E1988_20[(((int)&((Recovered_Vtable_003E1988 *)0)->field_20) == 32) ? 1 : -1];
#endif
