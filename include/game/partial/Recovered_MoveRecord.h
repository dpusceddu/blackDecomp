/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_MOVERECORD_H
#define RECOVERED_MOVERECORD_H
#include "ps2/prelude.h"

typedef struct Recovered_MoveRecord {
    u8 opaque_0[4];
    f32 field_4; /* PS2 +0x4 */
    f32 field_8; /* PS2 +0x8 */
    f32 field_C; /* PS2 +0xC */
    f32 field_10; /* PS2 +0x10 */
    f32 field_14; /* PS2 +0x14 */
    f32 field_18; /* PS2 +0x18 */
    u8 field_1C; /* PS2 +0x1C */
    u8 field_1D; /* PS2 +0x1D */
} Recovered_MoveRecord;
typedef char assert_Recovered_MoveRecord_4[(((int)&((Recovered_MoveRecord *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_MoveRecord_8[(((int)&((Recovered_MoveRecord *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_MoveRecord_C[(((int)&((Recovered_MoveRecord *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_MoveRecord_10[(((int)&((Recovered_MoveRecord *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_MoveRecord_14[(((int)&((Recovered_MoveRecord *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_MoveRecord_18[(((int)&((Recovered_MoveRecord *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_MoveRecord_1C[(((int)&((Recovered_MoveRecord *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_MoveRecord_1D[(((int)&((Recovered_MoveRecord *)0)->field_1D) == 29) ? 1 : -1];
#endif
