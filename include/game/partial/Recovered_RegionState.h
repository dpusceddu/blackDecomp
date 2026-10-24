/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_REGIONSTATE_H
#define RECOVERED_REGIONSTATE_H
#include "ps2/prelude.h"

typedef struct Recovered_RegionState {
    u64 field_0; /* PS2 +0x0 */
    u8 opaque_8[268];
    void * field_114; /* PS2 +0x114 */
    u32 field_118; /* PS2 +0x118 */
    u8 field_11C; /* PS2 +0x11C */
    u8 field_11D; /* PS2 +0x11D */
    u8 opaque_11E[6];
    u32 field_124; /* PS2 +0x124 */
    u8 opaque_128[24];
    s128 field_140; /* PS2 +0x140 */
    s128 field_150; /* PS2 +0x150 */
} Recovered_RegionState;
typedef char assert_Recovered_RegionState_0[(((int)&((Recovered_RegionState *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_RegionState_114[(((int)&((Recovered_RegionState *)0)->field_114) == 276) ? 1 : -1];
typedef char assert_Recovered_RegionState_118[(((int)&((Recovered_RegionState *)0)->field_118) == 280) ? 1 : -1];
typedef char assert_Recovered_RegionState_11C[(((int)&((Recovered_RegionState *)0)->field_11C) == 284) ? 1 : -1];
typedef char assert_Recovered_RegionState_11D[(((int)&((Recovered_RegionState *)0)->field_11D) == 285) ? 1 : -1];
typedef char assert_Recovered_RegionState_124[(((int)&((Recovered_RegionState *)0)->field_124) == 292) ? 1 : -1];
typedef char assert_Recovered_RegionState_140[(((int)&((Recovered_RegionState *)0)->field_140) == 320) ? 1 : -1];
typedef char assert_Recovered_RegionState_150[(((int)&((Recovered_RegionState *)0)->field_150) == 336) ? 1 : -1];
#endif
