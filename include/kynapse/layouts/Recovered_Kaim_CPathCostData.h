/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_KAIM_CPATHCOSTDATA_H
#define RECOVERED_KAIM_CPATHCOSTDATA_H
#include "ps2/prelude.h"

typedef struct Recovered_Kaim_CPathCostData {
    u32 field_0; /* PS2 +0x0 */
    u8 opaque_4[4];
    s32 field_8; /* PS2 +0x8 */
    s32 field_C; /* PS2 +0xC */
    f32 field_10; /* PS2 +0x10 */
} Recovered_Kaim_CPathCostData;
typedef char assert_Recovered_Kaim_CPathCostData_0[(((int)&((Recovered_Kaim_CPathCostData *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Kaim_CPathCostData_8[(((int)&((Recovered_Kaim_CPathCostData *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_Kaim_CPathCostData_C[(((int)&((Recovered_Kaim_CPathCostData *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_Kaim_CPathCostData_10[(((int)&((Recovered_Kaim_CPathCostData *)0)->field_10) == 16) ? 1 : -1];
#endif
