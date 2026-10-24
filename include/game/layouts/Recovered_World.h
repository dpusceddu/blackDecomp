/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_WORLD_H
#define RECOVERED_WORLD_H
#include "ps2/prelude.h"

typedef struct Recovered_World {
    u8 opaque_0[18840];
    s32 field_4998; /* PS2 +0x4998 */
    u8 opaque_499C[2172];
    s32 field_5218; /* PS2 +0x5218 */
    u8 opaque_521C[2172];
    s32 field_5A98; /* PS2 +0x5A98 */
    u8 opaque_5A9C[520];
    s32 field_5CA4; /* PS2 +0x5CA4 */
    u8 opaque_5CA8[1648];
    s32 field_6318; /* PS2 +0x6318 */
    u8 opaque_631C[2172];
    s32 field_6B98; /* PS2 +0x6B98 */
    u8 opaque_6B9C[2172];
    s32 field_7418; /* PS2 +0x7418 */
    u8 opaque_741C[2172];
    s32 field_7C98; /* PS2 +0x7C98 */
    u8 opaque_7C9C[2172];
    s32 field_8518; /* PS2 +0x8518 */
} Recovered_World;
typedef char assert_Recovered_World_4998[(((int)&((Recovered_World *)0)->field_4998) == 18840) ? 1 : -1];
typedef char assert_Recovered_World_5218[(((int)&((Recovered_World *)0)->field_5218) == 21016) ? 1 : -1];
typedef char assert_Recovered_World_5A98[(((int)&((Recovered_World *)0)->field_5A98) == 23192) ? 1 : -1];
typedef char assert_Recovered_World_5CA4[(((int)&((Recovered_World *)0)->field_5CA4) == 23716) ? 1 : -1];
typedef char assert_Recovered_World_6318[(((int)&((Recovered_World *)0)->field_6318) == 25368) ? 1 : -1];
typedef char assert_Recovered_World_6B98[(((int)&((Recovered_World *)0)->field_6B98) == 27544) ? 1 : -1];
typedef char assert_Recovered_World_7418[(((int)&((Recovered_World *)0)->field_7418) == 29720) ? 1 : -1];
typedef char assert_Recovered_World_7C98[(((int)&((Recovered_World *)0)->field_7C98) == 31896) ? 1 : -1];
typedef char assert_Recovered_World_8518[(((int)&((Recovered_World *)0)->field_8518) == 34072) ? 1 : -1];
#endif
