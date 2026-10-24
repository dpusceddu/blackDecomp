/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_HEURISTICMETABASE_H
#define RECOVERED_HEURISTICMETABASE_H
#include "ps2/prelude.h"

typedef struct Recovered_HeuristicMetaBase {
    u32 field_0; /* PS2 +0x0 */
    u32 field_4; /* PS2 +0x4 */
    u8 opaque_8[256];
    u32 field_108; /* PS2 +0x108 */
    s32 field_10C; /* PS2 +0x10C */
    u32 field_110; /* PS2 +0x110 */
} Recovered_HeuristicMetaBase;
typedef char assert_Recovered_HeuristicMetaBase_0[(((int)&((Recovered_HeuristicMetaBase *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_HeuristicMetaBase_4[(((int)&((Recovered_HeuristicMetaBase *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_HeuristicMetaBase_108[(((int)&((Recovered_HeuristicMetaBase *)0)->field_108) == 264) ? 1 : -1];
typedef char assert_Recovered_HeuristicMetaBase_10C[(((int)&((Recovered_HeuristicMetaBase *)0)->field_10C) == 268) ? 1 : -1];
typedef char assert_Recovered_HeuristicMetaBase_110[(((int)&((Recovered_HeuristicMetaBase *)0)->field_110) == 272) ? 1 : -1];
#endif
