/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_QUERYPATH_H
#define RECOVERED_QUERYPATH_H
#include "ps2/prelude.h"

typedef struct Recovered_QueryPath {
    u8 opaque_0[8];
    s32 field_8; /* PS2 +0x8 */
    u8 opaque_C[8];
    s32 field_14; /* PS2 +0x14 */
    s32 field_18; /* PS2 +0x18 */
} Recovered_QueryPath;
typedef char assert_Recovered_QueryPath_8[(((int)&((Recovered_QueryPath *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_QueryPath_14[(((int)&((Recovered_QueryPath *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_QueryPath_18[(((int)&((Recovered_QueryPath *)0)->field_18) == 24) ? 1 : -1];
#endif
