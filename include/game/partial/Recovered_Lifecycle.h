/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_LIFECYCLE_H
#define RECOVERED_LIFECYCLE_H
#include "ps2/prelude.h"

typedef struct Recovered_Lifecycle {
    s32 field_0; /* PS2 +0x0 */
    u8 opaque_4[76];
    u32 field_50; /* PS2 +0x50 */
    s32 field_54; /* PS2 +0x54 */
    s32 field_58; /* PS2 +0x58 */
    u8 opaque_5C[2];
    s16 field_5E; /* PS2 +0x5E */
    u8 opaque_60[8];
    s32 field_68; /* PS2 +0x68 */
    u8 opaque_6C[4];
    s32 field_70; /* PS2 +0x70 */
    u8 opaque_74[2364];
    s32 field_9B0; /* PS2 +0x9B0 */
} Recovered_Lifecycle;
typedef char assert_Recovered_Lifecycle_0[(((int)&((Recovered_Lifecycle *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Lifecycle_50[(((int)&((Recovered_Lifecycle *)0)->field_50) == 80) ? 1 : -1];
typedef char assert_Recovered_Lifecycle_54[(((int)&((Recovered_Lifecycle *)0)->field_54) == 84) ? 1 : -1];
typedef char assert_Recovered_Lifecycle_58[(((int)&((Recovered_Lifecycle *)0)->field_58) == 88) ? 1 : -1];
typedef char assert_Recovered_Lifecycle_5E[(((int)&((Recovered_Lifecycle *)0)->field_5E) == 94) ? 1 : -1];
typedef char assert_Recovered_Lifecycle_68[(((int)&((Recovered_Lifecycle *)0)->field_68) == 104) ? 1 : -1];
typedef char assert_Recovered_Lifecycle_70[(((int)&((Recovered_Lifecycle *)0)->field_70) == 112) ? 1 : -1];
typedef char assert_Recovered_Lifecycle_9B0[(((int)&((Recovered_Lifecycle *)0)->field_9B0) == 2480) ? 1 : -1];
#endif
