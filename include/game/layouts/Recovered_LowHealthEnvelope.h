/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_LOWHEALTHENVELOPE_H
#define RECOVERED_LOWHEALTHENVELOPE_H
#include "ps2/prelude.h"

typedef struct Recovered_LowHealthEnvelope {
    s32 field_0; /* PS2 +0x0 */
    f32 field_4; /* PS2 +0x4 */
    f32 field_8; /* PS2 +0x8 */
    f32 field_C; /* PS2 +0xC */
    f32 field_10; /* PS2 +0x10 */
    f32 field_14; /* PS2 +0x14 */
    u32 field_18; /* PS2 +0x18 */
    u32 field_1C; /* PS2 +0x1C */
    f32 field_20; /* PS2 +0x20 */
    f32 field_24; /* PS2 +0x24 */
    f32 field_28; /* PS2 +0x28 */
    f32 field_2C; /* PS2 +0x2C */
    f32 field_30; /* PS2 +0x30 */
    u8 opaque_34[8];
    f32 field_3C; /* PS2 +0x3C */
    f32 field_40; /* PS2 +0x40 */
    u8 field_44; /* PS2 +0x44 */
    u8 field_45; /* PS2 +0x45 */
    u8 field_46; /* PS2 +0x46 */
    u8 field_47; /* PS2 +0x47 */
    u8 field_48; /* PS2 +0x48 */
    u8 field_49; /* PS2 +0x49 */
    u8 field_4A; /* PS2 +0x4A */
    u8 field_4B; /* PS2 +0x4B */
    u8 field_4C; /* PS2 +0x4C */
    u8 field_4D; /* PS2 +0x4D */
} Recovered_LowHealthEnvelope;
typedef char assert_Recovered_LowHealthEnvelope_0[(((int)&((Recovered_LowHealthEnvelope *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_4[(((int)&((Recovered_LowHealthEnvelope *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_8[(((int)&((Recovered_LowHealthEnvelope *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_C[(((int)&((Recovered_LowHealthEnvelope *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_10[(((int)&((Recovered_LowHealthEnvelope *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_14[(((int)&((Recovered_LowHealthEnvelope *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_18[(((int)&((Recovered_LowHealthEnvelope *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_1C[(((int)&((Recovered_LowHealthEnvelope *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_20[(((int)&((Recovered_LowHealthEnvelope *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_24[(((int)&((Recovered_LowHealthEnvelope *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_28[(((int)&((Recovered_LowHealthEnvelope *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_2C[(((int)&((Recovered_LowHealthEnvelope *)0)->field_2C) == 44) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_30[(((int)&((Recovered_LowHealthEnvelope *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_3C[(((int)&((Recovered_LowHealthEnvelope *)0)->field_3C) == 60) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_40[(((int)&((Recovered_LowHealthEnvelope *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_44[(((int)&((Recovered_LowHealthEnvelope *)0)->field_44) == 68) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_45[(((int)&((Recovered_LowHealthEnvelope *)0)->field_45) == 69) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_46[(((int)&((Recovered_LowHealthEnvelope *)0)->field_46) == 70) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_47[(((int)&((Recovered_LowHealthEnvelope *)0)->field_47) == 71) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_48[(((int)&((Recovered_LowHealthEnvelope *)0)->field_48) == 72) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_49[(((int)&((Recovered_LowHealthEnvelope *)0)->field_49) == 73) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_4A[(((int)&((Recovered_LowHealthEnvelope *)0)->field_4A) == 74) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_4B[(((int)&((Recovered_LowHealthEnvelope *)0)->field_4B) == 75) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_4C[(((int)&((Recovered_LowHealthEnvelope *)0)->field_4C) == 76) ? 1 : -1];
typedef char assert_Recovered_LowHealthEnvelope_4D[(((int)&((Recovered_LowHealthEnvelope *)0)->field_4D) == 77) ? 1 : -1];
#endif
