/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DB760_H
#define RECOVERED_VTABLE_003DB760_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DB760 {
    u64 field_0; /* PS2 +0x0 */
    u8 opaque_8[16];
    u32 field_18; /* PS2 +0x18 */
    u8 field_1C; /* PS2 +0x1C */
    u8 opaque_1D[3];
    void * field_20; /* PS2 +0x20 */
    s32 field_24; /* PS2 +0x24 */
    f32 field_28; /* PS2 +0x28 */
} Recovered_Vtable_003DB760;
typedef char assert_Recovered_Vtable_003DB760_0[(((int)&((Recovered_Vtable_003DB760 *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB760_18[(((int)&((Recovered_Vtable_003DB760 *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB760_1C[(((int)&((Recovered_Vtable_003DB760 *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB760_20[(((int)&((Recovered_Vtable_003DB760 *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB760_24[(((int)&((Recovered_Vtable_003DB760 *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB760_28[(((int)&((Recovered_Vtable_003DB760 *)0)->field_28) == 40) ? 1 : -1];
#endif
