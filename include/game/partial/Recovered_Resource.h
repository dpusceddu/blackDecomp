/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RESOURCE_H
#define RECOVERED_RESOURCE_H
#include "ps2/prelude.h"

typedef struct Recovered_Resource {
    u8 opaque_0[8];
    s32 field_8; /* PS2 +0x8 */
} Recovered_Resource;
typedef char assert_Recovered_Resource_8[(((int)&((Recovered_Resource *)0)->field_8) == 8) ? 1 : -1];
#endif
