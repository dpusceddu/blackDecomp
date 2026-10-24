/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RWAFORMAT_H
#define RECOVERED_RWAFORMAT_H
#include "ps2/prelude.h"

typedef struct Recovered_RwaFormat {
    s32 field_0; /* PS2 +0x0 */
    u8 opaque_4[4];
    u32 field_8; /* PS2 +0x8 */
    u8 opaque_C[2];
    u8 field_E; /* PS2 +0xE */
    u8 field_F; /* PS2 +0xF */
    u8 opaque_10[4];
    s32 field_14; /* PS2 +0x14 */
    u8 opaque_18[4];
} Recovered_RwaFormat;
typedef char assert_Recovered_RwaFormat_0[(((int)&((Recovered_RwaFormat *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_RwaFormat_8[(((int)&((Recovered_RwaFormat *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_RwaFormat_E[(((int)&((Recovered_RwaFormat *)0)->field_E) == 14) ? 1 : -1];
typedef char assert_Recovered_RwaFormat_F[(((int)&((Recovered_RwaFormat *)0)->field_F) == 15) ? 1 : -1];
typedef char assert_Recovered_RwaFormat_14[(((int)&((Recovered_RwaFormat *)0)->field_14) == 20) ? 1 : -1];
#endif
