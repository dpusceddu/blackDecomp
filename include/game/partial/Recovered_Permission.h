/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PERMISSION_H
#define RECOVERED_PERMISSION_H
#include "ps2/prelude.h"

typedef struct Recovered_Permission {
    u8 opaque_0[2];
    u8 field_2; /* PS2 +0x2 */
} Recovered_Permission;
typedef char assert_Recovered_Permission_2[(((int)&((Recovered_Permission *)0)->field_2) == 2) ? 1 : -1];
#endif
