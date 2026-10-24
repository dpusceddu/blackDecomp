/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_FRAME_H
#define RECOVERED_FRAME_H
#include "ps2/prelude.h"

typedef struct Recovered_Frame {
    u8 opaque_0[18840];
    s32 field_4998; /* PS2 +0x4998 */
    u8 opaque_499C[44];
    u8 field_49C8; /* PS2 +0x49C8 */
    u8 opaque_49C9[2127];
    s32 field_5218; /* PS2 +0x5218 */
    u8 opaque_521C[44];
    u8 field_5248; /* PS2 +0x5248 */
    u8 opaque_5249[2119];
    void * field_5A90; /* PS2 +0x5A90 */
    u8 opaque_5A94[4];
    s32 field_5A98; /* PS2 +0x5A98 */
    u8 opaque_5A9C[44];
    u8 field_5AC8; /* PS2 +0x5AC8 */
    u8 opaque_5AC9[2127];
    s32 field_6318; /* PS2 +0x6318 */
    u8 opaque_631C[44];
    u8 field_6348; /* PS2 +0x6348 */
    u8 opaque_6349[2127];
    s32 field_6B98; /* PS2 +0x6B98 */
    u8 opaque_6B9C[44];
    u8 field_6BC8; /* PS2 +0x6BC8 */
    u8 opaque_6BC9[2127];
    s32 field_7418; /* PS2 +0x7418 */
    u8 opaque_741C[44];
    u8 field_7448; /* PS2 +0x7448 */
    u8 opaque_7449[2127];
    s32 field_7C98; /* PS2 +0x7C98 */
    u8 opaque_7C9C[44];
    u8 field_7CC8; /* PS2 +0x7CC8 */
    u8 opaque_7CC9[2127];
    s32 field_8518; /* PS2 +0x8518 */
    u8 opaque_851C[44];
    u8 field_8548; /* PS2 +0x8548 */
} Recovered_Frame;
typedef char assert_Recovered_Frame_4998[(((int)&((Recovered_Frame *)0)->field_4998) == 18840) ? 1 : -1];
typedef char assert_Recovered_Frame_49C8[(((int)&((Recovered_Frame *)0)->field_49C8) == 18888) ? 1 : -1];
typedef char assert_Recovered_Frame_5218[(((int)&((Recovered_Frame *)0)->field_5218) == 21016) ? 1 : -1];
typedef char assert_Recovered_Frame_5248[(((int)&((Recovered_Frame *)0)->field_5248) == 21064) ? 1 : -1];
typedef char assert_Recovered_Frame_5A90[(((int)&((Recovered_Frame *)0)->field_5A90) == 23184) ? 1 : -1];
typedef char assert_Recovered_Frame_5A98[(((int)&((Recovered_Frame *)0)->field_5A98) == 23192) ? 1 : -1];
typedef char assert_Recovered_Frame_5AC8[(((int)&((Recovered_Frame *)0)->field_5AC8) == 23240) ? 1 : -1];
typedef char assert_Recovered_Frame_6318[(((int)&((Recovered_Frame *)0)->field_6318) == 25368) ? 1 : -1];
typedef char assert_Recovered_Frame_6348[(((int)&((Recovered_Frame *)0)->field_6348) == 25416) ? 1 : -1];
typedef char assert_Recovered_Frame_6B98[(((int)&((Recovered_Frame *)0)->field_6B98) == 27544) ? 1 : -1];
typedef char assert_Recovered_Frame_6BC8[(((int)&((Recovered_Frame *)0)->field_6BC8) == 27592) ? 1 : -1];
typedef char assert_Recovered_Frame_7418[(((int)&((Recovered_Frame *)0)->field_7418) == 29720) ? 1 : -1];
typedef char assert_Recovered_Frame_7448[(((int)&((Recovered_Frame *)0)->field_7448) == 29768) ? 1 : -1];
typedef char assert_Recovered_Frame_7C98[(((int)&((Recovered_Frame *)0)->field_7C98) == 31896) ? 1 : -1];
typedef char assert_Recovered_Frame_7CC8[(((int)&((Recovered_Frame *)0)->field_7CC8) == 31944) ? 1 : -1];
typedef char assert_Recovered_Frame_8518[(((int)&((Recovered_Frame *)0)->field_8518) == 34072) ? 1 : -1];
typedef char assert_Recovered_Frame_8548[(((int)&((Recovered_Frame *)0)->field_8548) == 34120) ? 1 : -1];
#endif
