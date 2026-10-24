/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003E0610_H
#define RECOVERED_VTABLE_003E0610_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003E0610 {
    u8 opaque_0[16];
    u128 field_10; /* PS2 +0x10 */
    u128 field_20; /* PS2 +0x20 */
    u128 field_30; /* PS2 +0x30 */
    u128 field_40; /* PS2 +0x40 */
} Recovered_Vtable_003E0610;
typedef char assert_Recovered_Vtable_003E0610_10[(((int)&((Recovered_Vtable_003E0610 *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E0610_20[(((int)&((Recovered_Vtable_003E0610 *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E0610_30[(((int)&((Recovered_Vtable_003E0610 *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E0610_40[(((int)&((Recovered_Vtable_003E0610 *)0)->field_40) == 64) ? 1 : -1];
#endif
