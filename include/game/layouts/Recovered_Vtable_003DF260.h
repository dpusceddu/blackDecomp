/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DF260_H
#define RECOVERED_VTABLE_003DF260_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DF260 {
    s32 field_0; /* PS2 +0x0 */
    u8 opaque_4[12];
    s128 field_10; /* PS2 +0x10 */
    u8 field_20; /* PS2 +0x20 */
} Recovered_Vtable_003DF260;
typedef char assert_Recovered_Vtable_003DF260_0[(((int)&((Recovered_Vtable_003DF260 *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DF260_10[(((int)&((Recovered_Vtable_003DF260 *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DF260_20[(((int)&((Recovered_Vtable_003DF260 *)0)->field_20) == 32) ? 1 : -1];
#endif
