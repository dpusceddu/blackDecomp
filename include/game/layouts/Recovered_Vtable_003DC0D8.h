/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DC0D8_H
#define RECOVERED_VTABLE_003DC0D8_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DC0D8 {
    u8 opaque_0[16];
    void * field_10; /* PS2 +0x10 */
    u8 opaque_14[4];
    s32 field_18; /* PS2 +0x18 */
    void * field_1C; /* PS2 +0x1C */
} Recovered_Vtable_003DC0D8;
typedef char assert_Recovered_Vtable_003DC0D8_10[(((int)&((Recovered_Vtable_003DC0D8 *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC0D8_18[(((int)&((Recovered_Vtable_003DC0D8 *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC0D8_1C[(((int)&((Recovered_Vtable_003DC0D8 *)0)->field_1C) == 28) ? 1 : -1];
#endif
