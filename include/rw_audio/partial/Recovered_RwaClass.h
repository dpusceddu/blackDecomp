/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RWACLASS_H
#define RECOVERED_RWACLASS_H
#include "ps2/prelude.h"

typedef struct Recovered_RwaClass {
    u8 opaque_0[72];
    s32 field_48; /* PS2 +0x48 */
} Recovered_RwaClass;
typedef char assert_Recovered_RwaClass_48[(((int)&((Recovered_RwaClass *)0)->field_48) == 72) ? 1 : -1];
#endif
