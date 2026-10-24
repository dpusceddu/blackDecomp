/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_MODEFFECTS_REGIONS_H
#define RECOVERED_MODEFFECTS_REGIONS_H
#include "ps2/prelude.h"

typedef struct Recovered_ModEffects_Regions {
    s32 field_0; /* PS2 +0x0 */
    s32 field_4; /* PS2 +0x4 */
} Recovered_ModEffects_Regions;
typedef char assert_Recovered_ModEffects_Regions_0[(((int)&((Recovered_ModEffects_Regions *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_ModEffects_Regions_4[(((int)&((Recovered_ModEffects_Regions *)0)->field_4) == 4) ? 1 : -1];
#endif
