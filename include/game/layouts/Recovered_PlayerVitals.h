/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PLAYERVITALS_H
#define RECOVERED_PLAYERVITALS_H
#include "ps2/prelude.h"

typedef struct Recovered_PlayerVitals {
    u8 opaque_0[760];
    f32 field_2F8; /* PS2 +0x2F8 */
    u8 opaque_2FC[48];
    void * field_32C; /* PS2 +0x32C */
    u8 opaque_330[92];
    s32 field_38C; /* PS2 +0x38C */
    u8 opaque_390[1297];
    s8 field_8A1; /* PS2 +0x8A1 */
    u8 opaque_8A2[16];
    u8 field_8B2; /* PS2 +0x8B2 */
} Recovered_PlayerVitals;
typedef char assert_Recovered_PlayerVitals_2F8[(((int)&((Recovered_PlayerVitals *)0)->field_2F8) == 760) ? 1 : -1];
typedef char assert_Recovered_PlayerVitals_32C[(((int)&((Recovered_PlayerVitals *)0)->field_32C) == 812) ? 1 : -1];
typedef char assert_Recovered_PlayerVitals_38C[(((int)&((Recovered_PlayerVitals *)0)->field_38C) == 908) ? 1 : -1];
typedef char assert_Recovered_PlayerVitals_8A1[(((int)&((Recovered_PlayerVitals *)0)->field_8A1) == 2209) ? 1 : -1];
typedef char assert_Recovered_PlayerVitals_8B2[(((int)&((Recovered_PlayerVitals *)0)->field_8B2) == 2226) ? 1 : -1];
#endif
