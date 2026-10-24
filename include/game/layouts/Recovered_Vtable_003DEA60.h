/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DEA60_H
#define RECOVERED_VTABLE_003DEA60_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DEA60 {
    void * field_0; /* PS2 +0x0 */
    u8 opaque_4[12];
    u128 field_10; /* PS2 +0x10 */
} Recovered_Vtable_003DEA60;
typedef char assert_Recovered_Vtable_003DEA60_0[(((int)&((Recovered_Vtable_003DEA60 *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DEA60_10[(((int)&((Recovered_Vtable_003DEA60 *)0)->field_10) == 16) ? 1 : -1];
#endif
