/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ISSET0C_H
#define RECOVERED_ISSET0C_H
#include "ps2/prelude.h"

typedef struct Recovered_IsSet0C {
    u8 opaque_0[12];
    s32 field_C; /* PS2 +0xC */
} Recovered_IsSet0C;
typedef char assert_Recovered_IsSet0C_C[(((int)&((Recovered_IsSet0C *)0)->field_C) == 12) ? 1 : -1];
#endif
