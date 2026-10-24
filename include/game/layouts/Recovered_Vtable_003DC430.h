/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DC430_H
#define RECOVERED_VTABLE_003DC430_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DC430 {
    u8 opaque_0[160];
    u128 field_A0; /* PS2 +0xA0 */
    u8 opaque_B0[64];
    u128 field_F0; /* PS2 +0xF0 */
    u8 opaque_100[16];
    f32 field_110; /* PS2 +0x110 */
    u8 field_114; /* PS2 +0x114 */
    u8 field_115; /* PS2 +0x115 */
    u8 opaque_116[1];
    u8 field_117; /* PS2 +0x117 */
} Recovered_Vtable_003DC430;
typedef char assert_Recovered_Vtable_003DC430_A0[(((int)&((Recovered_Vtable_003DC430 *)0)->field_A0) == 160) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC430_F0[(((int)&((Recovered_Vtable_003DC430 *)0)->field_F0) == 240) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC430_110[(((int)&((Recovered_Vtable_003DC430 *)0)->field_110) == 272) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC430_114[(((int)&((Recovered_Vtable_003DC430 *)0)->field_114) == 276) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC430_115[(((int)&((Recovered_Vtable_003DC430 *)0)->field_115) == 277) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC430_117[(((int)&((Recovered_Vtable_003DC430 *)0)->field_117) == 279) ? 1 : -1];
#endif
