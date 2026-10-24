/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DD810_H
#define RECOVERED_VTABLE_003DD810_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DD810 {
    void * field_0; /* PS2 +0x0 */
    void * field_4; /* PS2 +0x4 */
    u8 opaque_8[12];
    u8 field_14; /* PS2 +0x14 */
    u8 field_15; /* PS2 +0x15 */
    u8 opaque_16[10];
    s128 field_20; /* PS2 +0x20 */
} Recovered_Vtable_003DD810;
typedef char assert_Recovered_Vtable_003DD810_0[(((int)&((Recovered_Vtable_003DD810 *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DD810_4[(((int)&((Recovered_Vtable_003DD810 *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DD810_14[(((int)&((Recovered_Vtable_003DD810 *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DD810_15[(((int)&((Recovered_Vtable_003DD810 *)0)->field_15) == 21) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DD810_20[(((int)&((Recovered_Vtable_003DD810 *)0)->field_20) == 32) ? 1 : -1];
#endif
