/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_FOLLOWER_H
#define RECOVERED_FOLLOWER_H
#include "ps2/prelude.h"

typedef struct Recovered_Follower {
    void * field_0; /* PS2 +0x0 */
    void * field_4; /* PS2 +0x4 */
    void * field_8; /* PS2 +0x8 */
    void * field_C; /* PS2 +0xC */
    void * field_10; /* PS2 +0x10 */
    f32 field_14; /* PS2 +0x14 */
    f32 field_18; /* PS2 +0x18 */
    f32 field_1C; /* PS2 +0x1C */
    f32 field_20; /* PS2 +0x20 */
    f32 field_24; /* PS2 +0x24 */
    f32 field_28; /* PS2 +0x28 */
    s32 field_2C; /* PS2 +0x2C */
    u8 opaque_30[4];
    f32 field_34; /* PS2 +0x34 */
    u8 field_38; /* PS2 +0x38 */
    u8 opaque_39[3];
    void * field_3C; /* PS2 +0x3C */
    f32 field_40; /* PS2 +0x40 */
    f32 field_44; /* PS2 +0x44 */
} Recovered_Follower;
typedef char assert_Recovered_Follower_0[(((int)&((Recovered_Follower *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Follower_4[(((int)&((Recovered_Follower *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_Follower_8[(((int)&((Recovered_Follower *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_Follower_C[(((int)&((Recovered_Follower *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_Follower_10[(((int)&((Recovered_Follower *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_Follower_14[(((int)&((Recovered_Follower *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_Follower_18[(((int)&((Recovered_Follower *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_Follower_1C[(((int)&((Recovered_Follower *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_Follower_20[(((int)&((Recovered_Follower *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_Follower_24[(((int)&((Recovered_Follower *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_Follower_28[(((int)&((Recovered_Follower *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_Follower_2C[(((int)&((Recovered_Follower *)0)->field_2C) == 44) ? 1 : -1];
typedef char assert_Recovered_Follower_34[(((int)&((Recovered_Follower *)0)->field_34) == 52) ? 1 : -1];
typedef char assert_Recovered_Follower_38[(((int)&((Recovered_Follower *)0)->field_38) == 56) ? 1 : -1];
typedef char assert_Recovered_Follower_3C[(((int)&((Recovered_Follower *)0)->field_3C) == 60) ? 1 : -1];
typedef char assert_Recovered_Follower_40[(((int)&((Recovered_Follower *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_Follower_44[(((int)&((Recovered_Follower *)0)->field_44) == 68) ? 1 : -1];
#endif
