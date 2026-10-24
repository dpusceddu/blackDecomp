/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_BOTHIDS28_H
#define RECOVERED_BOTHIDS28_H
#include "ps2/prelude.h"

typedef struct Recovered_BothIds28 {
    u8 opaque_0[40];
    s32 field_28; /* PS2 +0x28 */
    u8 opaque_2C[4];
    s32 field_30; /* PS2 +0x30 */
} Recovered_BothIds28;
typedef char assert_Recovered_BothIds28_28[(((int)&((Recovered_BothIds28 *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_BothIds28_30[(((int)&((Recovered_BothIds28 *)0)->field_30) == 48) ? 1 : -1];
#endif
