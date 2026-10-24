/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PLAYBACKSTATE_H
#define RECOVERED_PLAYBACKSTATE_H
#include "ps2/prelude.h"

typedef struct Recovered_PlaybackState {
    u8 opaque_0[140];
    s32 field_8C; /* PS2 +0x8C */
    u8 opaque_90[36];
    s32 field_B4; /* PS2 +0xB4 */
    u8 opaque_B8[36];
    s32 field_DC; /* PS2 +0xDC */
    u8 opaque_E0[36];
    s32 field_104; /* PS2 +0x104 */
    u8 opaque_108[36];
    s32 field_12C; /* PS2 +0x12C */
    u8 opaque_130[36];
    s32 field_154; /* PS2 +0x154 */
    u8 opaque_158[36];
    s32 field_17C; /* PS2 +0x17C */
    u8 opaque_180[36];
    s32 field_1A4; /* PS2 +0x1A4 */
    u8 opaque_1A8[36];
    s32 field_1CC; /* PS2 +0x1CC */
    u8 opaque_1D0[1976];
    u32 field_988; /* PS2 +0x988 */
    s32 field_98C; /* PS2 +0x98C */
    u8 opaque_990[4];
    s32 field_994; /* PS2 +0x994 */
} Recovered_PlaybackState;
typedef char assert_Recovered_PlaybackState_8C[(((int)&((Recovered_PlaybackState *)0)->field_8C) == 140) ? 1 : -1];
typedef char assert_Recovered_PlaybackState_B4[(((int)&((Recovered_PlaybackState *)0)->field_B4) == 180) ? 1 : -1];
typedef char assert_Recovered_PlaybackState_DC[(((int)&((Recovered_PlaybackState *)0)->field_DC) == 220) ? 1 : -1];
typedef char assert_Recovered_PlaybackState_104[(((int)&((Recovered_PlaybackState *)0)->field_104) == 260) ? 1 : -1];
typedef char assert_Recovered_PlaybackState_12C[(((int)&((Recovered_PlaybackState *)0)->field_12C) == 300) ? 1 : -1];
typedef char assert_Recovered_PlaybackState_154[(((int)&((Recovered_PlaybackState *)0)->field_154) == 340) ? 1 : -1];
typedef char assert_Recovered_PlaybackState_17C[(((int)&((Recovered_PlaybackState *)0)->field_17C) == 380) ? 1 : -1];
typedef char assert_Recovered_PlaybackState_1A4[(((int)&((Recovered_PlaybackState *)0)->field_1A4) == 420) ? 1 : -1];
typedef char assert_Recovered_PlaybackState_1CC[(((int)&((Recovered_PlaybackState *)0)->field_1CC) == 460) ? 1 : -1];
typedef char assert_Recovered_PlaybackState_988[(((int)&((Recovered_PlaybackState *)0)->field_988) == 2440) ? 1 : -1];
typedef char assert_Recovered_PlaybackState_98C[(((int)&((Recovered_PlaybackState *)0)->field_98C) == 2444) ? 1 : -1];
typedef char assert_Recovered_PlaybackState_994[(((int)&((Recovered_PlaybackState *)0)->field_994) == 2452) ? 1 : -1];
#endif
