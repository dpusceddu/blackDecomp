/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RWASOUND_H
#define RECOVERED_RWASOUND_H
#include "ps2/prelude.h"

typedef struct Recovered_RwaSound {
    u64 field_0; /* PS2 +0x0 */
    u8 opaque_8[88];
    u64 field_60; /* PS2 +0x60 */
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
    u8 opaque_D8[8];
    u64 field_E0; /* PS2 +0xE0 */
    u64 field_E8; /* PS2 +0xE8 */
    u64 field_F0; /* PS2 +0xF0 */
    u8 opaque_F8[32];
    u32 field_118; /* PS2 +0x118 */
} Recovered_RwaSound;
typedef char assert_Recovered_RwaSound_0[(((int)&((Recovered_RwaSound *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_RwaSound_60[(((int)&((Recovered_RwaSound *)0)->field_60) == 96) ? 1 : -1];
typedef char assert_Recovered_RwaSound_68[(((int)&((Recovered_RwaSound *)0)->field_68) == 104) ? 1 : -1];
typedef char assert_Recovered_RwaSound_70[(((int)&((Recovered_RwaSound *)0)->field_70) == 112) ? 1 : -1];
typedef char assert_Recovered_RwaSound_80[(((int)&((Recovered_RwaSound *)0)->field_80) == 128) ? 1 : -1];
typedef char assert_Recovered_RwaSound_88[(((int)&((Recovered_RwaSound *)0)->field_88) == 136) ? 1 : -1];
typedef char assert_Recovered_RwaSound_90[(((int)&((Recovered_RwaSound *)0)->field_90) == 144) ? 1 : -1];
typedef char assert_Recovered_RwaSound_A0[(((int)&((Recovered_RwaSound *)0)->field_A0) == 160) ? 1 : -1];
typedef char assert_Recovered_RwaSound_A8[(((int)&((Recovered_RwaSound *)0)->field_A8) == 168) ? 1 : -1];
typedef char assert_Recovered_RwaSound_B0[(((int)&((Recovered_RwaSound *)0)->field_B0) == 176) ? 1 : -1];
typedef char assert_Recovered_RwaSound_C0[(((int)&((Recovered_RwaSound *)0)->field_C0) == 192) ? 1 : -1];
typedef char assert_Recovered_RwaSound_C8[(((int)&((Recovered_RwaSound *)0)->field_C8) == 200) ? 1 : -1];
typedef char assert_Recovered_RwaSound_D0[(((int)&((Recovered_RwaSound *)0)->field_D0) == 208) ? 1 : -1];
typedef char assert_Recovered_RwaSound_E0[(((int)&((Recovered_RwaSound *)0)->field_E0) == 224) ? 1 : -1];
typedef char assert_Recovered_RwaSound_E8[(((int)&((Recovered_RwaSound *)0)->field_E8) == 232) ? 1 : -1];
typedef char assert_Recovered_RwaSound_F0[(((int)&((Recovered_RwaSound *)0)->field_F0) == 240) ? 1 : -1];
typedef char assert_Recovered_RwaSound_118[(((int)&((Recovered_RwaSound *)0)->field_118) == 280) ? 1 : -1];
#endif
