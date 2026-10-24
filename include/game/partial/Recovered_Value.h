/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VALUE_H
#define RECOVERED_VALUE_H
#include "ps2/prelude.h"

typedef struct Recovered_Value {
    u8 opaque_0[4];
    void * field_4; /* PS2 +0x4 */
    u8 opaque_8[20];
    s32 field_1C; /* PS2 +0x1C */
} Recovered_Value;
typedef char assert_Recovered_Value_4[(((int)&((Recovered_Value *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_Value_1C[(((int)&((Recovered_Value *)0)->field_1C) == 28) ? 1 : -1];
#endif
