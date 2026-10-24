/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003E0748_H
#define RECOVERED_VTABLE_003E0748_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003E0748 {
    u8 opaque_0[416];
    s32 field_1A0; /* PS2 +0x1A0 */
    void * field_1A4; /* PS2 +0x1A4 */
    s32 field_1A8; /* PS2 +0x1A8 */
    u8 opaque_1AC[12];
    s32 field_1B8; /* PS2 +0x1B8 */
} Recovered_Vtable_003E0748;
typedef char assert_Recovered_Vtable_003E0748_1A0[(((int)&((Recovered_Vtable_003E0748 *)0)->field_1A0) == 416) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E0748_1A4[(((int)&((Recovered_Vtable_003E0748 *)0)->field_1A4) == 420) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E0748_1A8[(((int)&((Recovered_Vtable_003E0748 *)0)->field_1A8) == 424) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E0748_1B8[(((int)&((Recovered_Vtable_003E0748 *)0)->field_1B8) == 440) ? 1 : -1];
#endif
