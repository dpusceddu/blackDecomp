/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RWSTREAMPS2_H
#define RECOVERED_RWSTREAMPS2_H
#include "ps2/prelude.h"

typedef struct Recovered_RwStreamPS2 {
    s32 field_0; /* PS2 +0x0 */
    u8 opaque_4[8];
    s32 field_C; /* PS2 +0xC */
    s32 field_10; /* PS2 +0x10 */
    s32 field_14; /* PS2 +0x14 */
    u8 opaque_18[4];
    s32 field_1C; /* PS2 +0x1C */
} Recovered_RwStreamPS2;
typedef char assert_Recovered_RwStreamPS2_0[(((int)&((Recovered_RwStreamPS2 *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_RwStreamPS2_C[(((int)&((Recovered_RwStreamPS2 *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_RwStreamPS2_10[(((int)&((Recovered_RwStreamPS2 *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_RwStreamPS2_14[(((int)&((Recovered_RwStreamPS2 *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_RwStreamPS2_1C[(((int)&((Recovered_RwStreamPS2 *)0)->field_1C) == 28) ? 1 : -1];
#endif
