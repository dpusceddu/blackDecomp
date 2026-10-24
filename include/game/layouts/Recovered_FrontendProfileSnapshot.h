/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_FRONTENDPROFILESNAPSHOT_H
#define RECOVERED_FRONTENDPROFILESNAPSHOT_H
#include "ps2/prelude.h"

typedef struct Recovered_FrontendProfileSnapshot {
    u32 field_0; /* PS2 +0x0 */
    u32 field_4; /* PS2 +0x4 */
    u8 field_8; /* PS2 +0x8 */
    u8 opaque_9[15];
    u32 field_18; /* PS2 +0x18 */
    u32 field_1C; /* PS2 +0x1C */
    u8 opaque_20[72];
    u64 field_68; /* PS2 +0x68 */
    u64 field_70; /* PS2 +0x70 */
    u8 opaque_78[8];
    u64 field_80; /* PS2 +0x80 */
    u64 field_88; /* PS2 +0x88 */
    u64 field_90; /* PS2 +0x90 */
    u8 opaque_98[8];
    u64 field_A0; /* PS2 +0xA0 */
    u64 field_A8; /* PS2 +0xA8 */
    u64 field_B0; /* PS2 +0xB0 */
    u8 opaque_B8[8];
    u64 field_C0; /* PS2 +0xC0 */
    u64 field_C8; /* PS2 +0xC8 */
    u64 field_D0; /* PS2 +0xD0 */
    u8 opaque_D8[16];
    s64 field_E8; /* PS2 +0xE8 */
    s64 field_F0; /* PS2 +0xF0 */
    u8 opaque_F8[8];
    s64 field_100; /* PS2 +0x100 */
    s64 field_108; /* PS2 +0x108 */
    s64 field_110; /* PS2 +0x110 */
    u8 opaque_118[8];
    s64 field_120; /* PS2 +0x120 */
    s64 field_128; /* PS2 +0x128 */
    s64 field_130; /* PS2 +0x130 */
    u8 opaque_138[8];
    s64 field_140; /* PS2 +0x140 */
    s64 field_148; /* PS2 +0x148 */
    s64 field_150; /* PS2 +0x150 */
    s64 field_158; /* PS2 +0x158 */
    s64 field_160; /* PS2 +0x160 */
    s64 field_168; /* PS2 +0x168 */
    s64 field_170; /* PS2 +0x170 */
    s64 field_178; /* PS2 +0x178 */
    s64 field_180; /* PS2 +0x180 */
    s64 field_188; /* PS2 +0x188 */
    s64 field_190; /* PS2 +0x190 */
    s64 field_198; /* PS2 +0x198 */
    s64 field_1A0; /* PS2 +0x1A0 */
    s64 field_1A8; /* PS2 +0x1A8 */
    s64 field_1B0; /* PS2 +0x1B0 */
    s64 field_1B8; /* PS2 +0x1B8 */
    s64 field_1C0; /* PS2 +0x1C0 */
    s64 field_1C8; /* PS2 +0x1C8 */
    s64 field_1D0; /* PS2 +0x1D0 */
    s64 field_1D8; /* PS2 +0x1D8 */
    s64 field_1E0; /* PS2 +0x1E0 */
    u8 opaque_1E8[1437];
    u8 field_785; /* PS2 +0x785 */
    u8 opaque_786[2];
    s32 field_788; /* PS2 +0x788 */
} Recovered_FrontendProfileSnapshot;
typedef char assert_Recovered_FrontendProfileSnapshot_0[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_4[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_8[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_18[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_1C[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_68[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_68) == 104) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_70[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_70) == 112) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_80[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_80) == 128) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_88[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_88) == 136) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_90[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_90) == 144) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_A0[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_A0) == 160) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_A8[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_A8) == 168) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_B0[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_B0) == 176) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_C0[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_C0) == 192) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_C8[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_C8) == 200) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_D0[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_D0) == 208) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_E8[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_E8) == 232) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_F0[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_F0) == 240) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_100[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_100) == 256) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_108[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_108) == 264) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_110[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_110) == 272) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_120[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_120) == 288) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_128[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_128) == 296) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_130[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_130) == 304) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_140[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_140) == 320) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_148[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_148) == 328) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_150[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_150) == 336) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_158[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_158) == 344) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_160[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_160) == 352) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_168[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_168) == 360) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_170[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_170) == 368) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_178[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_178) == 376) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_180[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_180) == 384) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_188[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_188) == 392) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_190[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_190) == 400) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_198[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_198) == 408) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_1A0[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_1A0) == 416) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_1A8[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_1A8) == 424) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_1B0[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_1B0) == 432) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_1B8[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_1B8) == 440) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_1C0[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_1C0) == 448) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_1C8[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_1C8) == 456) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_1D0[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_1D0) == 464) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_1D8[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_1D8) == 472) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_1E0[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_1E0) == 480) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_785[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_785) == 1925) ? 1 : -1];
typedef char assert_Recovered_FrontendProfileSnapshot_788[(((int)&((Recovered_FrontendProfileSnapshot *)0)->field_788) == 1928) ? 1 : -1];
#endif
