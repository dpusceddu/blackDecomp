/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_OPERATIONS_H
#define RECOVERED_OPERATIONS_H
#include "ps2/prelude.h"

typedef struct Recovered_Operations {
    u8 opaque_0[108];
    s16 field_6C; /* PS2 +0x6C */
    u8 opaque_6E[2326];
    u32 field_984; /* PS2 +0x984 */
    u8 opaque_988[16];
    s32 field_998; /* PS2 +0x998 */
} Recovered_Operations;
typedef char assert_Recovered_Operations_6C[(((int)&((Recovered_Operations *)0)->field_6C) == 108) ? 1 : -1];
typedef char assert_Recovered_Operations_984[(((int)&((Recovered_Operations *)0)->field_984) == 2436) ? 1 : -1];
typedef char assert_Recovered_Operations_998[(((int)&((Recovered_Operations *)0)->field_998) == 2456) ? 1 : -1];
#endif
