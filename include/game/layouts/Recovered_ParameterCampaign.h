/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PARAMETERCAMPAIGN_H
#define RECOVERED_PARAMETERCAMPAIGN_H
#include "ps2/prelude.h"

typedef struct Recovered_ParameterCampaign {
    u8 opaque_0[4];
    s32 field_4; /* PS2 +0x4 */
    s32 field_8; /* PS2 +0x8 */
    s32 field_C; /* PS2 +0xC */
    s32 field_10; /* PS2 +0x10 */
    s32 field_14; /* PS2 +0x14 */
    s32 field_18; /* PS2 +0x18 */
    f32 field_1C; /* PS2 +0x1C */
    u8 opaque_20[24];
    s32 field_38; /* PS2 +0x38 */
    s32 field_3C; /* PS2 +0x3C */
    s32 field_40; /* PS2 +0x40 */
    u8 opaque_44[12];
    u8 field_50; /* PS2 +0x50 */
} Recovered_ParameterCampaign;
typedef char assert_Recovered_ParameterCampaign_4[(((int)&((Recovered_ParameterCampaign *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_ParameterCampaign_8[(((int)&((Recovered_ParameterCampaign *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_ParameterCampaign_C[(((int)&((Recovered_ParameterCampaign *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_ParameterCampaign_10[(((int)&((Recovered_ParameterCampaign *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_ParameterCampaign_14[(((int)&((Recovered_ParameterCampaign *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_ParameterCampaign_18[(((int)&((Recovered_ParameterCampaign *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_ParameterCampaign_1C[(((int)&((Recovered_ParameterCampaign *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_ParameterCampaign_38[(((int)&((Recovered_ParameterCampaign *)0)->field_38) == 56) ? 1 : -1];
typedef char assert_Recovered_ParameterCampaign_3C[(((int)&((Recovered_ParameterCampaign *)0)->field_3C) == 60) ? 1 : -1];
typedef char assert_Recovered_ParameterCampaign_40[(((int)&((Recovered_ParameterCampaign *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_ParameterCampaign_50[(((int)&((Recovered_ParameterCampaign *)0)->field_50) == 80) ? 1 : -1];
#endif
