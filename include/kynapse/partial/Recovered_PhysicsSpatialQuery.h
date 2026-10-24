/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PHYSICSSPATIALQUERY_H
#define RECOVERED_PHYSICSSPATIALQUERY_H
#include "ps2/prelude.h"

typedef struct Recovered_PhysicsSpatialQuery {
    void * field_0; /* PS2 +0x0 */
    u8 opaque_4[12];
    u128 field_10; /* PS2 +0x10 */
    u128 field_20; /* PS2 +0x20 */
    u128 field_30; /* PS2 +0x30 */
    u128 field_40; /* PS2 +0x40 */
    u16 field_50; /* PS2 +0x50 */
    u8 opaque_52[10094];
    s32 field_27C0; /* PS2 +0x27C0 */
    u16 field_27C4; /* PS2 +0x27C4 */
    u8 opaque_27C6[18];
    s32 field_27D8; /* PS2 +0x27D8 */
    u32 field_27DC; /* PS2 +0x27DC */
} Recovered_PhysicsSpatialQuery;
typedef char assert_Recovered_PhysicsSpatialQuery_0[(((int)&((Recovered_PhysicsSpatialQuery *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_PhysicsSpatialQuery_10[(((int)&((Recovered_PhysicsSpatialQuery *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_PhysicsSpatialQuery_20[(((int)&((Recovered_PhysicsSpatialQuery *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_PhysicsSpatialQuery_30[(((int)&((Recovered_PhysicsSpatialQuery *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_PhysicsSpatialQuery_40[(((int)&((Recovered_PhysicsSpatialQuery *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_PhysicsSpatialQuery_50[(((int)&((Recovered_PhysicsSpatialQuery *)0)->field_50) == 80) ? 1 : -1];
typedef char assert_Recovered_PhysicsSpatialQuery_27C0[(((int)&((Recovered_PhysicsSpatialQuery *)0)->field_27C0) == 10176) ? 1 : -1];
typedef char assert_Recovered_PhysicsSpatialQuery_27C4[(((int)&((Recovered_PhysicsSpatialQuery *)0)->field_27C4) == 10180) ? 1 : -1];
typedef char assert_Recovered_PhysicsSpatialQuery_27D8[(((int)&((Recovered_PhysicsSpatialQuery *)0)->field_27D8) == 10200) ? 1 : -1];
typedef char assert_Recovered_PhysicsSpatialQuery_27DC[(((int)&((Recovered_PhysicsSpatialQuery *)0)->field_27DC) == 10204) ? 1 : -1];
#endif
